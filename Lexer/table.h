#pragma once
#ifndef __LEX_table
#define __LEX_table

#include <vector>
#include <utility>
#include "./lexp.h"

#include <string>

namespace frontend
{
    static std::vector<std::pair<const char*, enum frontend::token_t>> table_keywords = 
    {
        {"null", _NULL},
        {"not", NOT_W},
        {"and", AND_W},
        {"or",  OR},

        {"include",     INCLUDE},
        {"import",      IMPORT},
        {"static",      STATIC},
        {"const",       CONST},
        {"if",          IF},
        {"else",        ELSE},
        {"while",       WHILE},
        {"continue",    CONTINUE},
        {"break",       BREAK},
        {"for",         FOR},
        {"in",          IN},
        {"func",        FUNC},
        {"return",      RETURN},
        {"class",       CLASS},
        {"inherit",     INHERIT},
        {"public",      PUBLIC},
        {"private",     PRIVATE},
        {"protected",   PROTECTED},
        {"virtual",     VIRTUAL},
        {"override",    OVERRIDE}


    };
    // OperatorsGrammaticSymbols
    static std::vector<std::pair<const char*, enum frontend::token_t>> table_ogs = {
        // 3
        {"<<=", LEFT_SHIFT_ASSIGN},
        {">>=", RIGHT_SHIFT_ASSIGN},
        // 2
        {"{$",  CODE_BEGIN},
        {"$}",  CODE_END},
        {"++",  INCREMENT},
        {"--",  DECREMENT},
        {"==",  EQUAL},
        {"!=",  NOT_EQUAL},
        {">=",  MORE_OR_EQUAL},
        {"<=",  LESS_OR_EQUAL},
        {"<<",  LEFT_SHIFT},
        {">>",  RIGHT_SHIFT},
        {"+=",  ADD_ASSIGN},
        {"-=",  SUB_ASSIGN},
        {"*=",  MUL_ASSIGN},
        {"/=",  DIV_ASSIGN},
        {"%=",  MOD_ASSIGN},
        {"&=",  BIT_AND_ASSIGN},
        {"|=",  BIT_OR_ASSIGN},
        {"^=",  XOR_ASSIGN},
        {"->",  ARROW},
        {"::",  DCOLON},
        {"&&",  AND},
        {"||",  OR},
        // 1
        {"\\",  BACKSLASH},
        {"(",   OPEN_PARENTHESES},
        {")",   CLOSE_PARENTHESES},
        {"{",   OPEN_BRACES},
        {"}",   CLOSE_BRACES},
        {"[",   OPEN_BRACKET},
        {"]",   CLOSE_BRACKET},
        {";",   SEMICOLON},
        {":",   COLON},
        {",",   COMMA},
        {".",   POINT},
        {"!",   NOT},
        {"+",   PLUS},
        {"-",   MINUS},
        {"*",   ASTERISK},
        {"/",   SLASH},
        {"%",   PERCENT},
        {"~",   INVERSION},
        {"&",   BIT_AND},
        {"|",   BIT_OR},
        {"^",   XOR},
        {">",   MORE},
        {"<",   LESS},
        {"=",   ASSIGN}
    };



    /*
    @return UNKNOWN if key is not found
    */
    enum frontend::token_t getValue(const std::vector<std::pair<const char*, enum frontend::token_t>>& table, const std::string &key);
} 
#endif