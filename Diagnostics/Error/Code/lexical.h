#pragma once
#ifndef __LEXICAL__ENUM_h
#define __LEXICAL__ENUM_h 1.0
namespace diagnostic
{
    enum lexical_e {

        // Comment
        MCNC,       // The multiline comment is not closed

        // Unknown token
        UNREC,      // Unrecognized token

        // ID
        LIDL,       // The identifier length is too long

        // String
        UNIC,       // Unicode expression can't decode
        CSNC,       // The constant string is not closed

        // Numeric
        TMDPN,      // To many decimal points in number
        EHND,       // Exponent has no digits
    };

}

#endif