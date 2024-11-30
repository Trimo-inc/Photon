#include "./lexp.h"
#include "./table.h"

bool frontend::isSpace(char symbol)
{
    return (symbol == ' ' || symbol == '\t');
}

using std::ios;
frontend::Lexer::Lexer(const std::string_view &filename) :
file_r(std::string(filename), ios::binary | ios::in | ios::trunc), code_c(0), pos(0), impr(nullptr), path_(filename){}

frontend::Lexer::~Lexer(void)
{
    if (file_r.is_open())
        file_r.close();
}

frontend::Token frontend::Lexer::next() &
{
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

    if (this->file_r.eof()) {
        this->token.type = frontend::EOF_FILE;
        return this->token;
    }
    if (this->peek(1)) {
        if (this->code_c) {
            // Preprocessing
            in_line();
            std::string word = this->read_word();
            if (!word.empty()) {
                this->token.type = frontend::getValue(word);
                if (this->token.type == frontend::UNKNOWN) {
                    // is not keyword

                }
                
                switch (this->token.type)
                {
                    case INCLUDE:
                    {
                        this->including();
                        break;
                    }
                    case IMPORT:
                    {

                    }
                }
                    
            }
        }
    } else {
        this->read_line();
        this->token.type = frontend::token_t::ENDLINE;
    }
    return this->token;
}

char frontend::Lexer::peek(std::size_t n) const
{
    std::size_t position = this->pos + n;
    return (position >= this->buffer.length()) ? ('\0') : (this->buffer[position]);
}
char frontend::Lexer::next_s(void)
{
    ++this->pos;
    return peek(0);
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
    unsigned char s = this->peek(0);
    if (std::isalpha(s) || s == '_') {
        while (s && (std::isalnum(s) || s == '_'))
        {
            s = this->next_s();
            word += s;
        }
    }
    return word;
}


/*
|===================|
| Preprocessor part |
|===================|
*/
//

void frontend::Lexer::in_line(void)
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
                break;
            }
        }
        ++i;
    } while(t);
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