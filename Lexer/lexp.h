#pragma once
#ifndef __LEXer_Preprocessor
#define __LEXer_Preprocessor

#include <string>
#include <fstream>
#include <vector>

namespace frontend
{
    enum token_t {
        TEXT,
        CODE_BEGIN, // '{$'
        CODE_END,   // '$}'
        ENDLINE,    // '\\n' | '\\r'
        EOF_FILE,
        // Identifier
        ID,
        // Base math operator 'expr operator expr' | 'operator expr' | 'expr operator'
        PLUS,       // '+'
        MINUS,      // '-'
        ASTERISK,   // '*'
        SLASH,      // '/'
        PERCENT,    // '%'
        INCREMENT,  // '++'
        DECREMENT,  // '--'
        // Comparison operators
        EQUAL,      // '=='
        NOT_EQUAL,  // '!='
        MORE,       // '>'
        LESS,       // '<'
        MORE_OR_EQUAL,  // '>='
        LESS_OR_EQUAL,  // '<='
        // Logic operators
        NOT,        // '!'  | 'not'
        AND,        // '&&' | 'and'
        OR,         // '||' | 'or'
        // Bitwise operators
        INVERSION,  // '~'
        BIT_AND,    // '&'
        BIT_OR,     // '|'
        XOR,        // '^'
        LEFT_SHIFT, // '<<'
        RIGHT_SHIFT,// '>>'
        // Compound assignment
        ASSIGN,     // '='
        ADD_ASSIGN, // '+='
        SUB_ASSIGN, // '-='
        MUL_ASSIGN, // '*='
        DIV_ASSIGN, // '/='
        MOD_ASSIGN, // '%='
        BIT_AND_ASSIGN,     // '&='
        BIT_OR_ASSIGN,      // '|='
        XOR_ASSIGN,         // '^='
        LEFT_SHIFT_ASSIGN,  // '<<='
        RIGHT_SHIFT_ASSIGN, // '>>='
        // Stables
        OPEN_PARENTHESES,   // '('
        CLOSE_PARENTHESES,  // ')'
        OPEN_BRACES,        // '{'
        CLOSE_BRACES,       // '}'
        OPEN_BRACKET,       // '['
        CLOSE_BRACKET,      // ']'
        // Other symbols
        SEMICOLON,          // ';'
        COLON,              // ':'
        COMMA,              // ','
        POINT,              // '.'
        BACKSLASH,          // '\\'
        ARROW,              // '->'
        // The scope extension operator
        DCOLON,             // '::'
        // Preprocesing words
        INCLUDE,            // 'include'
        IMPORT,             // 'import'
        // Keywords
        STATIC,             // 'static'
        CONST,              // 'const'
        IF,                 // 'if'
        ELSE,               // 'else'
        WHILE,              // 'while'
        CONTINUE,           // 'continue'
        BREAK,              // 'break'
        FOR,                // 'for'
        IN,                 // 'in'
        FUNC,               // 'func'
        RETURN,             // 'return'
        CLASS,              // 'class'
        INHERIT,            // 'inherit'
        PUBLIC,             // 'public'
        PRIVATE,            // 'private'
        PROTECTED,          // 'protected'
        VIRTUAL,            // 'virtual'
        OVERRIDE,           // 'override'
        // Small based types
        INT,                // example: 893
        FLOAT,              // examples: 3.091 | 4.21e-88
        HEX_INT,            // example: #10FAC9
        _NULL,              // 'null'
        // strings  
        STR,                // example: "hello" | 'hello'
    };
    struct Token {
        frontend::token_t type ;
        std::string       value;
    };
    
    namespace
    {
        unsigned int max_size = 256;
        std::vector<std::string> glob(const std::string_view& path);
    }


    class Lexer
    {
    public:
        Lexer(const std::string_view& filename);
        ~Lexer(void);
        struct frontend::Token next();
    private:
        char peek(std::size_t n);
        char next_s(void);
        void preprocessing  (void);
        void read_line      (void);
        bool is_operator    (void);
        bool is_keyword     (void);
        /*
        @brief CODE_BEGIN | CODE_END counter
        */
        unsigned int code_c;
        std::ifstream file_r;
        std::string buffer;
        std::size_t pos;
        struct frontend::Token token;
    };
}  



#endif