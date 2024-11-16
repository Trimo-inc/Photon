#include "./lexp.h"
#include "./table.h"
#include "lexp.h"
using std::ios;
frontend::Lexer::Lexer(const std::string_view &filename) :
file_r(std::string(filename), ios::binary | ios::in | ios::trunc), code_c(0), pos(0) {}

frontend::Lexer::~Lexer(void)
{
    if (file_r.is_open())
        file_r.close();
}

frontend::Token frontend::Lexer::next()
{
    if (this->peek(1)) {
        
    }
}

char frontend::Lexer::peek(std::size_t n)
{
    std::size_t position = this->pos + n;
    return (position >= this->buffer.length()) ? ('\0') : (this->buffer[position]);
}

char frontend::Lexer::next_s(void)
{
    this->pos++;
    return peek(0);
}

void frontend::Lexer::preprocessing(void)
{

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
