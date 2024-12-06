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