#pragma once
#ifndef __SourceLocation__h
#define __SourceLocation__h 1.0

#include <string>

namespace diagnostic
{
    /*
    Основная структура для хранения позиции и строки в файле, его имени
    */
    struct SourceLocation final
    {
        SourceLocation(void);
        SourceLocation(const std::string_view& path, const size_t position = 0, const size_t line = 0);
        std::string filepath;
        size_t position;
        size_t line;
        std::string to_string(void) const;
        bool operator==(const struct diagnostic::SourceLocation& other) const;
    };

}
#endif