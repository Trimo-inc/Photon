#pragma once
#ifndef __TRIE_LEX_v
#define __TRIE_LEX_v "1.0"
#include <string>

#include "../token_t.h"
#include "Node_lex.h"

namespace frontend
{
    /**
     * @brief Дерево, основанное на алгоритме Ахо-корасик.
     * Оно ищет полную строку, возвращая токен, или указывая на узел,
     * где приостановился поиск.
     * @details Дерево-Бор без суффиксных ссылок,
     * т.к. он лишь сравнивает полную строку, а не ищет подстроки.
     */
    class Trie_lex final
    {
    public:
        Trie_lex(void);
        ~Trie_lex(void);

        /**
         * @brief Вставляет строку в дерево с соответствующим токеном
         * @param[in] str Строка для вставки
         * @param[in] token Токен, соответствующий строке
         */
        void insert(const std::string_view& str, const frontend::token_t token);

        /**
         * @brief Удаляет из дерева строку для поиска
         * @details Он удаляет все узлы, у которых нет детей (all(this->children) == nullptr) 
         * @param[in] str Строка для удаления
         * @return 1 - при удачном удалении
         */
        bool remove(const std::string_view& str);



        /**
         * @brief Очищает дерево от всех узлов, кроме главного корня
         */
        void clear(void);


        /**
         * @brief Проверяет на полную строку
         * @param[out] str Сравнимая строка
         * @return Токен который соответсвует строке, иначе UNKNOWN
         */
        frontend::token_t eqfind(const std::string_view& str) const;

        /**
         * @brief Базовый итератор для дерева
         */
        struct iterator {
            iterator(frontend::Node_lex* node);
            /**
             * @brief Переходит к следующему узлу
             * @param[in] symbol Символ, к которому следует перейти
             * @return Удалось ли перейти
             */
            bool next(const char symbol);
            frontend::token_t get(void) const;
            frontend::Node_lex& operator*() const;
        private:
            Node_lex* current;
            
        }; 

        iterator begin() const;
        iterator end() const;
    private:
        /**
         * @brief Кол-во узлов в данном дереве
         */
        uint32_t count_nodes;

        /**
         * @brief Максимальное кол-во узлов
         * @details Если this->count_nodes == this->MAX_COUNT, то мы сериализуем часть данных
         */
        static const uint32_t MAX_COUNT = (2 << 10); 

        /**
         * @brief Дерево имеет данные, которые не убрались в MAX_COUNT и сериализованы? Да или нет
         */
        bool is_serialization;

        /**
         * @brief Корень дерева
         */
        frontend::Node_lex* root; 

        /**
         * @brief Сериализует данные (записывает в файл) 
         */
        void serialization(void);
        
        /**
         * @brief Вытаскивает из файла данные и заполняет дерево
         */
        void deserialization(void);
        
    };
}


#endif