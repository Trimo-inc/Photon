#pragma once
#ifndef __NODE_LEX_v
#define __NODE_LEX_v "1.0"
#include "../token_t.h"
#include <map>

namespace frontend
{
    struct Node_lex
    {
        Node_lex(void);
        bool terminale;
        frontend::token_t token;
        std::map<char, frontend::Node_lex*> children;
    };
}

#endif