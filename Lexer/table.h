#pragma once
#ifndef __LEX_table
#define __LEX_table

#include <unordered_map>
#include "./lexp.h"

namespace frontend
{
    static std::unordered_map<const char*, enum frontend::token_t> table = 
    {
        {"null", _NULL},
        {"{$",  CODE_BEGIN},
        {"$}",  CODE_END},
        {"+",   PLUS},
        {"-",   MINUS},
        {"*",   ASTERISK},
        {"/",   SLASH},
        {"%",   PERCENT},
        {"++",  INCREMENT},
        {"--",  DECREMENT},
        {"==",  EQUAL},
        {"!=",  NOT_EQUAL},
        {">",   MORE},
        {"<",   LESS},
        {">=",  MORE_OR_EQUAL},
        {"<=",  LESS_OR_EQUAL},
        {"!",   NOT},
        {"not", NOT},
        {"&&",  AND},
        {"and", AND},
        {"||",  OR},
        {"or",  OR},
        {"~",   INVERSION},
        {"&",   BIT_AND},
        {"|",   BIT_OR},
        {"^",   XOR},
        {"<<",  LEFT_SHIFT},
        {">>",  RIGHT_SHIFT},
        {"=",   ASSIGN},
        {"+=",  ADD_ASSIGN},
        {"-=",  SUB_ASSIGN},
        {"*=",  MUL_ASSIGN},
        {"/=",  DIV_ASSIGN},
        {"%=",  MOD_ASSIGN},
        {"&=",  BIT_AND_ASSIGN},
        {"|=",  BIT_OR_ASSIGN},
        {"^=",  XOR_ASSIGN},
        {"<<=", LEFT_SHIFT_ASSIGN},
        {">>=", RIGHT_SHIFT_ASSIGN},
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
        {"\\",  BACKSLASH},
        {"->",  ARROW},
        {"::",  DCOLON},

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
} 
#endif