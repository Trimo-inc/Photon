#pragma once
#ifndef WARN_TYPE__h
#define WARN_TYPE__h 1.0
namespace diagnostic
{
    enum warn_t
    {
        DCOR,       // The value of the number is overflowed
        HCOR,       // Hexadecimal character out of range
        OCOR,       // Octal character out of range
    };

}

#endif