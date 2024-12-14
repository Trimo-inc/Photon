#pragma once
#ifndef __ERROR__
#define __ERROR__ 1
#include <string>


#include "../SourceLocation/SourceLocation.h"


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


    /*
    Base error class
    */
    struct Error final
    {
        enum diagnostic::error_t type;
        
        struct diagnostic::SourceLocation location;
        std::string description;
    };

} 



#endif