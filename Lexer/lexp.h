#pragma once
#ifndef __LEXer_Preprocessor
#define __LEXer_Preprocessor

#include <string>
#include <fstream>
#include <vector>

#include "../Diagnostics/Error/Error.h"
#include "./token_t.h"

namespace frontend
{
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


/**
 * @version 1.0
 * @class Lexer
 * @brief Превращает из текста программы в лексические токены
 * @details   
 * Лексер или же токенизатор берёт на себя ответственность обнаружить лексему и привести её к нужному токену,
 * возможно превратив из числа "#aBCDeF" в нормализованное число "11 259 375" (без пробелов разумеется),
 * Имеется вывод ошибок и предупреждений
 * 
 */
    class Lexer final
    {
    public:
        Lexer(const std::string_view& filename);
        ~Lexer(void);
        /**
         * @brief Получает следующий токен. Если токен ERR, то следует учесть функцию Lexer::get_error();
         * @return Следующий токен
         */
        struct frontend::Token next() &;
        
        
        /// @result 255
        static std::size_t max_id_length; 
    private:
        /**
         * @brief Смотрит символ по индексу [this->pos + n] из this->buffer
         * @param[in] n Индекс от начала this->pos
         * @return Символ или '\0', если не удалось просмотреть
         */
        char peek(std::size_t n) const;
        
        /**
         * @brief Смотрит символ в utf-8 по индексу [(this->pos + n)]
         * @param[in] n Индекс от начала this->pos
         * @param[out] len При передачи любое значение.
         * Меняет своё значение - сколько байтов прочитал, если '\0', то символ не в utf-8
         * @return Символ utf-8
         */
        int  peek_utf8(std::size_t n, char& len) const;
        
        /**
         * @brief Читает последующий байт из this->buffer
         * @details
         * Увеличивает текущую позицию у this->buffer, т.е. (++this->pos)
         * Аналогичен вызову this->peek(0);
         * @return Следующий байт
         */
        char next_s(void);

        /**
         * @brief Проверяет, что следующий токен строка
         * @return Строка или нет
         */
        bool isString(void) const;

        /**
         * @brief Читает следующую строку в файловом буффере
         * @details Максимум читает до frontend::max_size и до точки с запятой (';')
         */
        void read_line(void);

        /**
         * @brief Читает строку
         * @details Перед вызовом this->read_string надо убедиться,
         * что следующий токен строка, с помощью this->isString() == true
         */
        void read_string(void);

        /**
         * @brief Читает число
         * @details Преобразует из различной формы в десятичную в виде строки
         * @return Если число, то возвращает true, иначе это другой токен
         */
        bool read_number(void);
        
        /**
         * 
         */
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
        bool is_error;
        struct diagnostic::Error error;
    };

}  



#endif