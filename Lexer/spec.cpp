#include "./table.h"
#include "./lexp.h"

#include <algorithm>
#include <cstring>

frontend::token_t frontend::getValue(const std::vector<std::pair<const char*, enum frontend::token_t>>& table, const std::string &key)
{
    auto search = std::find_if(table.begin(), table.end(),
    [&key](const std::pair<const char*, enum frontend::token_t>& p) {
        return std::strcmp(p.first, key.c_str()) == 0;
    });
    return (search != table.end()) ? (search->second) : (frontend::UNKNOWN);
}

std::vector<std::string> frontend::glob(const std::string_view &path, frontend::Token &error)
{
    std::vector<std::string> v;

    return v;
}


bool frontend::isSpace(char symbol)
{
    return (symbol == ' ' || symbol == '\t');
}
bool frontend::isAlpha(int symbol)
{
    return (symbol >= 0x0041 && symbol <= 0x007A) ||  // A-Z, a-z (латинские буквы)
           (symbol >= 0x0400 && symbol <= 0x04FF) ||  // А-Я, а-я (кириллица)
           (symbol >= 0x0370 && symbol <= 0x03FF) ||  // Греческие буквы
           (symbol >= 0x2000 && symbol <= 0x200F);
}


/*
Unicode symbols to UTF8 
*/
std::string frontend::unicode_to_utf8(int unicode)
{
    std::string result;

    if (unicode < 0x80) {
        result += static_cast<char>(unicode);
    } else if (unicode < 0x800) {
        result += static_cast<char>((unicode >> 6) | 0xC0);
        result += static_cast<char>((unicode & 0x3F) | 0x80);
    } else if (unicode < 0x10000) {
        result += static_cast<char>((unicode >> 12) | 0xE0);
        result += static_cast<char>(((unicode >> 6) & 0x3F) | 0x80);
        result += static_cast<char>((unicode & 0x3F) | 0x80);
    } else if (unicode < 0x110000) {
        result += static_cast<char>((unicode >> 18) | 0xF0);
        result += static_cast<char>(((unicode >> 12) & 0x3F) | 0x80);
        result += static_cast<char>(((unicode >> 6) & 0x3F) | 0x80);
        result += static_cast<char>((unicode & 0x3F) | 0x80);
    } 

    return result;
}