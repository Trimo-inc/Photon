#include "./Trie_lex.h"
#include "./Node_lex.h"
#include "Trie_lex.h"

#include <vector>


/*

    Node_lex

*/
frontend::Node_lex::Node_lex() : terminale(false), token(frontend::token_t::UNKNOWN){}

/*

    Trie_lex

*/
frontend::Trie_lex::Trie_lex(void)
        : count_nodes(0), is_serialization(false), root(new frontend::Node_lex()){}

frontend::Trie_lex::~Trie_lex(void)
{
    this->clear();
    delete this->root;
}

void frontend::Trie_lex::insert(const std::string_view &str, const frontend::token_t token)
{
    frontend::Node_lex* node = this->root;
    for (const char ch : str) {

        if (node->children.find(ch) == node->children.end()) {
            node->children[ch] = new Node_lex();
            ++this->count_nodes;
        }
        node = node->children[ch];
    }
    node->terminale = true;
    node->token = token;
}

bool frontend::Trie_lex::remove(const std::string_view &str)
{
    std::vector<std::pair<struct frontend::Node_lex*, char>> path; // Сохраняем пути к нашей строке
    struct frontend::Node_lex* node = root;
    bool ret = false;

    for (const char ch : str) {
        if (node->children.find(ch) == node->children.end())
            return ret;
        path.emplace_back(node, ch);
        node = node->children[ch];
    }
    // this->root не в счёт
    if (path.size() > 1) {
        std::vector<std::pair<struct frontend::Node_lex*, char>>::iterator end = --path.end();
        std::vector<std::pair<struct frontend::Node_lex*, char>>::iterator start = path.begin();

        while (end != start) {
            char s_child = end->second;

            // Если нет детей, то удаляем узел, перемещаясь вверх и удаляя ссылку
            ret = (end->first->children.size() == 0);
            if (ret) {
                delete end->first;
                --end;
                end->first->children.erase(s_child);
            } else break;
        }
    }
    return ret;
}
