#include "Lexer/lexp.h"
#include "Lexer/table.h"
#include "LTEST/lex_test.h"

#include <iostream>

#include <Windows.h>



int main (int argc, char* argv[])
{
    SetConsoleOutputCP( CP_UTF8 );
    setvbuf( stdout, nullptr, _IONBF, 0 );

    LTEST::run(std::cout, "LTest/file.fn");
    return 0;
}