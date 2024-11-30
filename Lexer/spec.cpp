#include "./table.h"

frontend::token_t frontend::getValue(const std::string &key)
{
    auto search = frontend::table.find(key.c_str());
    return (search != frontend::table.end()) ? (search->second) : (frontend::UNKNOWN);
}