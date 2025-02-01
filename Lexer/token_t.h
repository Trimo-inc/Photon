#pragma once
#ifndef __TOKEN_T__h
#define __TOKEN_T__h 1.0
namespace frontend {
    enum token_t {
        UNKNOWN,
        ERROR,

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
        NOT,        // '!'
        NOT_W,      // 'not' alias
        AND,        // '&&' 
        AND_W,      // 'and' alias
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
        HEX_INT,            // example: #10FAC9 (not used in subsequent processing phases)
        _NULL,              // 'null'
        // strings
        STR, // @brief Обычная строка
        /**
         * @brief Форматированная строка
         * @example: f"hello \n{name}"
         */
        F_STR,            
        
    };
}
#endif