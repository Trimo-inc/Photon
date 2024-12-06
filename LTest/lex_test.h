#pragma once
#ifndef __LTEST__
#define __LTEST__
#include "../Lexer/lexp.h"
#include <ostream>

namespace LTEST {
    std::string to_string(const frontend::token_t& tt);
    void run(std::ostream& osm, const std::string_view& path);
}
#endif