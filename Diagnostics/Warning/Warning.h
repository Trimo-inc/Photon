#pragma once
#ifndef WARNING_h
#define WARNING_h 1.0

#include "../SourceLocation/SourceLocation.h"
#include "./warn_type.h"
namespace diagnostic
{
    struct Warning final
    {
        enum diagnostic::warn_t type;
        struct diagnostic::SourceLocation location;
        std::string description;
        std::string context; // text code
    };

}

#endif