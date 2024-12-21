#pragma once
#ifndef __ERROR__h
#define __ERROR__h 1
#include <string>


#include "../SourceLocation/SourceLocation.h"
#include "./Code/lexical.h"
#include "./Code/syntax.h"


namespace diagnostic
{
    /*
    Тип ошибки
    */
    enum error_t
    {
        LEXICAL,
        SYNTAX,
        SEMANTIC,
        SEGMENTAL,
        RUNTIME,
        LINKING
    };

    union error_code {
        diagnostic::lexical_e lex;
        diagnostic::syntax_e  syn;
    };


    /*
    Base error class
    */
    struct Error final
    {
        enum diagnostic::error_t type;

        struct diagnostic::SourceLocation location;
        std::string description;
        std::string context; // text code
    };

} 



#endif