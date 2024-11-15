#pragma once
#ifndef __LEXer_Preprocessor

#include <string>

namespace fronted
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
        RIGHT_SHIFT_ASSIGN, // '>>'
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
        
        BACKSLASH,         // '\\'
        // The scope extension operator
        DCOLON,            // '::'
        // Keywords
        STATIC,            // 'static'
        CONST,             // 'const'
        IF,                // 'if'
        ELSE,              // 'else'
        WHILE,             // 'while'
        FOR,               // 'for'
        IN                // 'in'
    };
    struct Token {
        fronted::token_t type;
        std::string      value;
    };

}  



#endif