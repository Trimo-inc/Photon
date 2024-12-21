#pragma once
#ifndef __LEXer_Preprocessor
#define __LEXer_Preprocessor

#include <string>
#include <fstream>
#include <vector>

#include "../Diagnostics/Error/Error.h"

namespace frontend
{
    enum token_t {
        UNKNOWN,
        ERROR,
        // errors lexer


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
        /*
        Only Double Strings are used in the lexer AND parser operation
        STR, R_STR, F_STR practically not needed for work
        */
        DSTR,               // example: "hello"  
        STR,                // example: 'hello' 
        R_DSTR,             // example: r"Hello \n" -> "Hello \\\n"
        R_STR,              // example: r'Hello \n' -> 'Hello \\\n'
        F_DSTR,             // example: f"Hello {name}"
        F_STR,              // example: f'Hello {name}'
        /*
        example: rf"hello \n{name}" -> f"Hello \\\n{name}" OR
        example: fr"hello \n{name}" -> f"Hello \\\n{name}" */
        RF_DSTR,            
        
    };
    struct Token {
        frontend::token_t type ;
        std::string       value;
    };
    enum status : char {
        OK,
        NO,
        ERR
    };

    inline unsigned int max_size = 256;
    std::vector<std::string> glob(const std::string_view& path, frontend::Token& error);
    bool isSpace(char symbol);
    bool isAlpha(int  symbol); // using UTF8
    std::string unicode_to_utf8(int unicode);


/*

┏━ ┳┓    ----------]
┃  ┃┃┏┓┏ ----------]
┗━ ┻┛┗┛┗ umentation]
     
On russian (на русском):
Класс Лексера превращает из текста программы в лексические токены.
Лексер или же токенизатор берёт на себя ответственность обнаружить лексему и привести её к нужному токену,
возможно превратив из числа "#aBCDeF" в нормализованное число "11 259 375" (без пробелов разумеется),
подмечу важную тонкость, в целочисленных токенах всегда в символике находятся байты этого числа,
а не строка чисел.
Первый символ у типов токена INT, FLOAT имеют два числа 20 | 40, т.е. знак числа,
где 20 - положительное число, а 40 - отрицательное

Лексер способен обрабатывать только токены чисел, дабы упростить парсеру жизнь, но он не способен
выполнять действия импорта, этим занимает парсер и его "волшебная коробка лексеров",
также токенизатор не включает текстовые файлы.

*/


    class Lexer final
    {
    public:
        Lexer(const std::string_view& filename);
        ~Lexer(void);
        struct frontend::Token next() &;
        
        bool isOk(void);
        // default-value: 255
        static std::size_t max_id_length; 
    private:
        char peek(std::size_t n) const;
        int  peek_utf8(std::size_t n, char& len) const;
        char next_s(void);
        bool isString(void);
        void read_line(void);
        void read_string(void);
        bool read_number(void);
        void Rformat_str(void);
        void Rread_str(std::string& string);
        bool identifier_run(void); // true is identifier
        void operator_run(void);
        bool preprocessing(void); // If error -> return false; else true;
        status in_line(void);
        status passComment(void);
        void   skipSpace(void);

        void num_panic(std::size_t& index);
        std::string read_word   (void);
        void read_text(void);
        // Variables
        /*
        @brief CODE_BEGIN | CODE_END counter
        */
        unsigned int code_c;
        std::ifstream file_r;
        std::string buffer;
        std::size_t pos;
        struct frontend::Token token; 
        std::string path_;
        
        struct diagnostic::Error error;
    };

}  



#endif