#include "./lexp.h"
#include "./table.h"

#include <cstring>
#include <cstdint>
#include <cctype>
#include <math.h>

#include <boost\locale.hpp>
#include <locale>


#include "lexp.h"


using std::ios;
frontend::Lexer::Lexer(const std::string_view &filename) :
file_r(std::string(filename), ios::binary), code_c(0), pos(0), impr(nullptr), path_(filename)
{
    if (this->file_r.is_open()) {
        this->read_line();
    }
}

frontend::Lexer::~Lexer(void)
{
    if (file_r.is_open())
        file_r.close();
}

frontend::Token frontend::Lexer::next() &
{
    this->token.type = token_t::UNKNOWN;
    this->token.value.clear();
    // Important! It is necessary for the correct operation of the import or including
    if (this->impr) {
        this->token = this->impr->next();
        if (this->token.type == token_t::EOF_FILE) {
            this->token.value = this->impr->path_;
            delete this->impr;
            this->impr = nullptr;
        }
        return this->token;
    }
    if (this->peek(1)) {
        if (this->code_c) {
            if (this->preprocessing()) {
                if (!this->identifier_run()) {
                    this->operator_run();
                    if (this->isString())
                        this->read_string();
                }
            }
        } else {
            this->read_text();
        }
    } else {
        if (this->file_r.eof()) {
            this->token.type = frontend::EOF_FILE;
        } else {
            this->read_line();
            this->token.type = frontend::token_t::ENDLINE;
        }
    }

    return this->token;
}

bool frontend::Lexer::isOk(void)
{
    return (file_r.is_open());
}
char frontend::Lexer::peek(std::size_t n) const
{
    std::size_t position = this->pos + n;
    return (position >= this->buffer.length()) ? ('\0') : (this->buffer[position]);
}
int frontend::Lexer::peek_utf8(std::size_t n, char& len) const
{
    std::size_t position = this->pos + n;
    int symbol = 0;
    if (position < this->buffer.length()) {
        char byte = this->buffer[position];
        if ((byte & 0x80) == 0) {
            len = 1;
            symbol = byte;
        } else if ((byte & 0xE0) == 0xC0) {
            len = 2;
            symbol = ((byte & 0x1F) << 6) | (this->buffer[position + 1] & 0x3F);
        } else if ((byte & 0xF0) == 0xE0) {
            len = 3;
            symbol = ((byte & 0x0F) << 12) | ((this->buffer[position + 1] & 0x3F) << 6) | (this->buffer[position + 2] & 0x3F);
        } else if ((byte & 0xF8) == 0xF0) {
            len = 4;
            symbol = ((byte & 0x07) << 18) | ((this->buffer[position + 1] & 0x3F) << 12) | ((this->buffer[position + 2] & 0x3F) << 6) | (this->buffer[position + 3] & 0x3F);
        } else
            len = 0;
    }
    
    return symbol;
}
char frontend::Lexer::next_s(void)
{
    ++this->pos;
    return peek(0);
}

bool frontend::Lexer::isString(void)
{
    char n = this->peek(0);
    switch (n)
    {
        case 'r':
        case 'f':
        {
            n = this->peek(1);
            switch (n)
            {
                case 'r':
                case 'f':
                {
                    n = this->peek(2);
                    switch (n)
                    {
                        case '\'': case '\"': {++this->pos;}
                        default: return false;
                    }
                }
                case '\'':
                case '\"': {++this->pos; break;}
                default: return false;
            }
        }
        case '\'':
        case '\"': return true;
    }
    return false;
}


void frontend::Lexer::read_line(void)
{    
    this->buffer.clear();
    char r;
    char endl_c = 0;
    while (this->file_r.get(r)) {
        if ((r == '\r' || r == '\n') && (endl_c != r)) {
            endl_c = r;
            continue;
        } 
        
        if ((this->buffer.length() > frontend::max_size) && (!this->code_c || (this->code_c && r == ';') || endl_c) ) {
            this->pos = 0;
            if (endl_c)
                this->buffer += '\n';
            return;
        }
        this->buffer += r;
    }
}


void frontend::Lexer::read_string(void)
{
    char n;
    // offset pos for symbol \' or \"
    this->Rformat_str();
    bool is_nRstring = !(this->token.type == RF_DSTR || this->token.type == R_DSTR);
    char start = this->peek(0);
    this->token.value.clear();
    std::string str = "";
    do {
        if (n == start) {
            this->token.value = str;
            break;
        }
        n = this->next_s();
        if (n == '\\' && is_nRstring) {
            Rread_str(str);
        }
        str += n;
    } while(n);

    
}

void frontend::Lexer::Rformat_str()
{
    frontend::token_t& type = this->token.type; // alias
    char d = this->peek(0);
    switch (d)
    {
        case 'r': {
            type = token_t::R_DSTR;
            break;
        }
        case 'f': {
            type = token_t::F_DSTR;
            break;
        }
        default:
            return;
    }
    char n = this->next_s();
    if ((n != d) && (n == 'r' || n == 'f')) {
        ++this->pos;
        type = token_t::RF_DSTR;
    }
}

void frontend::Lexer::Rread_str(std::string &string)
{
    char n = this->next_s();
    switch (n) {
        case 'a': { n = '\a'; break;}
        case 'b': { n = '\b'; break;}
        case 't': { n = '\t'; break;}
        case 'n': { n = '\n'; break;}
        case 'v': { n = '\v'; break;}
        case 'f': { n = '\f'; break;}
        case 'r': { n = '\r'; break;}
        case 'e': { n = '\e'; }
        case '\'':
        case '\"':
            break;
        default:
        {
            unsigned int s = 0;
            char i = 2;
            if (n == 'x')
                ++this->pos;
            while (i) {
                n = next_s();
                if ((n > '0' || n < '9')) {
                    s += (n - '0') * (std::pow(8, i));
                } else string += n;
                --i;
                
            }
            if (s > UINT16_MAX) {
                this->token.type  = token_t::ERR_UNIC;
                this->token.value = s;
                return;
            }
            string += s;
        }
    }
    string += n;

}



std::string frontend::Lexer::read_word(void)
{
    std::string word = "";
    char lenght;
    int s = this->peek_utf8(0, lenght);
 
    int size = this->buffer.length();
    if (frontend::isAlpha(s) || s == '_') {
        while (s && (frontend::isAlpha(s) || (s >= '0' && s <= '9') || s == '_'))
        {
            this->pos += lenght;
            word += frontend::unicode_to_utf8(s);
            s = this->peek_utf8(0, lenght);
        }
    }
    return word;
}

void frontend::Lexer::read_text(void)
{
    this->operator_run();
    char n = this->peek(0);
    if (this->token.type == token_t::CODE_BEGIN) {
        
        // Значит встретилась конструкция {$$, а не CODE_BEGIN 
        if (n == '$') {
            // This is TEXT
            this->token.value += "{$";
            
        } else {
            // This is CODE_BEGIN
            ++this->code_c;
            return;
        }
        
    }
    this->token.type = token_t::TEXT;
    while (n && (n != '{')) {
        this->token.value += n;
        n = next_s();
    }
}

// [RUN]
bool frontend::Lexer::identifier_run(void)
{
    const std::string word = this->read_word(); // only ID
    bool ret = !word.empty();
    if (ret) {
        this->token.type = frontend::getValue(frontend::table_keywords, word);              
        switch (this->token.type)
        {
            case INCLUDE:
            {
                this->including();
                break;
            }
            case IMPORT:
            {
                //this->importing();
                break;
            }
            case UNKNOWN: {
                this->token.type = ID; this->token.value = word; break;}
        }
    }
    return ret;
}

void frontend::Lexer::operator_run(void)
{
    std::string op = "";
    for (auto& x : frontend::table_ogs) {
        const std::size_t len = std::strlen(x.first);
        if (len + this->pos <= this->buffer.length()) {
            op = this->buffer.substr(this->pos, len);
            if (std::strcmp(op.c_str(), x.first) == 0) {
                this->token.type = x.second;
                this->pos += len;
                return;
            }
        }
    }
}

/*
|===================|
| Preprocessor part |
|===================|
*/
//

bool frontend::Lexer::preprocessing(void)
{
    frontend::status st;
    // Preprocessing
    do {
        this->skipSpace();
        st = passComment();
        if (st == frontend::status::ERR)
            return false;
        st = in_line();
    } while (st != frontend::status::NO);
    return true;
}

frontend::status frontend::Lexer::in_line(void)
{
    unsigned int i = 0;
    char t;
    do {
        t = this->peek(i);
        if (t == '\\') {
            t = this->peek(i + 1);
            if (t == '\n' || t == '\r' ) {
                std::string cpy_buff = this->buffer.substr(0, this->buffer.length() - 2);
                cpy_buff[cpy_buff.length() - 1] = ' ';
                this->read_line();
                this->buffer = cpy_buff + this->buffer;
                return OK;
            }
        }
        ++i;
    } while(t);
    return NO;
}
frontend::status frontend::Lexer::passComment(void)
{
    char n = this->peek(0);
    const char slash = '/';
    const char astrk = '*';
    if (n == slash) {
        n = this->peek(1);
        switch (n) {
            case slash: { this->read_line(); return OK;}
            case astrk: {        
                do {
                    n = this->next_s();
                    if (!n) { read_line(); continue; }
                    if (this->buffer.empty()) { this->token.type = token_t::ERR_CNC; return ERR; }
                    if (n == astrk) {
                        n = next_s();
                        if (n == slash)
                            break;
                    }
                } while (true);
            }
        }
    }
    return NO;
}

void frontend::Lexer::skipSpace(void)
{
    std::size_t i = 0;
    char n;
    do {
        n = this->peek(i);
        ++i;
    } while (n && (frontend::isSpace(n)));
    this->pos += i - 1;
}

void frontend::Lexer::including(void)
{
    this->token = this->next();
    frontend::Token err;
    // Предполагаем, что это строка
    auto vec = glob(this->token.value, err);
    if (err.type == token_t::ERR_NFP) {
        this->token = err;
        return;
    }
    class Lexer* p = this;
    for (auto s = vec.cbegin(), e = vec.cend(); s != e; ++s) {
        p->impr = new Lexer{std::string_view{*s}};
        p = p->impr;
    }
}