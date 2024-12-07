#include "./lex_test.h"
#include "lex_test.h"

std::string LTEST::to_string(const frontend::token_t &tt)
{
    std::string ret;
    using frontend::token_t;
    switch (tt)
    {
    case token_t::UNKNOWN: { ret = "UNKNOWN"; break; }
    case token_t::TEXT: {ret = "TEXT"; break;}
    case token_t::CODE_BEGIN: { ret = "CODE_BEGIN"; break; }
    case token_t::CODE_END: { ret = "CODE_END"; break; }
    case token_t::ENDLINE: { ret = "ENDLINE"; break; }
    case token_t::EOF_FILE: {ret = "EOF_FILE"; break;}
    case token_t::ID: {ret = "ID"; break;}
    case token_t::_NULL: { ret = "NULL"; break; }
    case token_t::PLUS: {ret = "PLUS"; break;}
    case token_t::MINUS: { ret = "MINUS"; break; }
    case token_t::ASTERISK: { ret = "ASTERISK"; break; }
    case token_t::SLASH: { ret = "SLASH"; break; }
    case token_t::PERCENT: { ret = "PERCENT"; break; }
    case token_t::INCREMENT: { ret = "INCREMENT"; break; }
    case token_t::DECREMENT: { ret = "DECREMENT"; break; }
    case token_t::EQUAL: { ret = "EQUAL"; break; }
    case token_t::NOT_EQUAL: { ret = "NOT_EQUAL"; break; }
    case token_t::MORE: { ret = "MORE"; break; }
    case token_t::LESS: { ret = "LESS"; break; }
    case token_t::MORE_OR_EQUAL: { ret = "MORE_OR_EQUAL"; break; }
    case token_t::LESS_OR_EQUAL: { ret = "LESS_OR_EQUAL"; break; }
    case token_t::NOT: { ret = "NOT"; break; }
    case token_t::AND: { ret = "AND"; break; }
    case token_t::OR: { ret = "OR"; break; }
    case token_t::INVERSION: { ret = "INVERSION"; break; }
    case token_t::BIT_AND: { ret = "BIT_AND"; break; }
    case token_t::BIT_OR: { ret = "BIT_OR"; break; }
    case token_t::XOR: { ret = "XOR"; break; }
    case token_t::LEFT_SHIFT: { ret = "LEFT_SHIFT"; break; }
    case token_t::RIGHT_SHIFT: { ret = "RIGHT_SHIFT"; break; }
    case token_t::ASSIGN: { ret = "ASSIGN"; break; }
    case token_t::ADD_ASSIGN: { ret = "ADD_ASSIGN"; break; }
    case token_t::SUB_ASSIGN: { ret = "SUB_ASSIGN"; break; }
    case token_t::MUL_ASSIGN: { ret = "MUL_ASSIGN"; break; }
    case token_t::DIV_ASSIGN: { ret = "DIV_ASSIGN"; break; }
    case token_t::MOD_ASSIGN: { ret = "MOD_ASSIGN"; break; }
    case token_t::BIT_AND_ASSIGN: { ret = "BIT_AND_ASSIGN"; break; }
    case token_t::BIT_OR_ASSIGN: { ret = "BIT_OR_ASSIGN"; break; }
    case token_t::XOR_ASSIGN: { ret = "XOR_ASSIGN"; break; }
    case token_t::LEFT_SHIFT_ASSIGN: { ret = "LEFT_SHIFT_ASSIGN"; break; }
    case token_t::RIGHT_SHIFT_ASSIGN: { ret = "RIGHT_SHIFT_ASSIGN"; break; }
    case token_t::OPEN_PARENTHESES: { ret = "OPEN_PARENTHESES"; break; }
    case token_t::CLOSE_PARENTHESES: { ret = "CLOSE_PARENTHESES"; break; }
    case token_t::OPEN_BRACES: { ret = "OPEN_BRACES"; break; }
    case token_t::CLOSE_BRACES: { ret = "CLOSE_BRACES"; break; }
    case token_t::OPEN_BRACKET: { ret = "OPEN_BRACKET"; break; }
    case token_t::CLOSE_BRACKET: { ret = "CLOSE_BRACKET"; break; }
    case token_t::SEMICOLON: { ret = "SEMICOLON"; break; }
    case token_t::COLON: { ret = "COLON"; break; }
    case token_t::COMMA: { ret = "COMMA"; break; }
    case token_t::POINT: { ret = "POINT"; break; }
    case token_t::BACKSLASH: { ret = "BACKSLASH"; break; }
    case token_t::ARROW: { ret = "ARROW"; break; }
    case token_t::DCOLON: { ret = "DCOLON"; break; }
    case token_t::INCLUDE: { ret = "INCLUDE"; break; }
    case token_t::IMPORT: { ret = "IMPORT"; break; }
    case token_t::STATIC: { ret = "STATIC"; break; }
    case token_t::CONST: { ret = "CONST"; break; }
    case token_t::IF: { ret = "IF"; break; }
    case token_t::ELSE: { ret = "ELSE"; break; }
    case token_t::WHILE: { ret = "WHILE"; break; }
    case token_t::CONTINUE: { ret = "CONTINUE"; break; }
    case token_t::BREAK: { ret = "BREAK"; break; }
    case token_t::FOR: { ret = "FOR"; break; }
    case token_t::IN: { ret = "IN"; break; }
    case token_t::FUNC: { ret = "FUNC"; break; }
    case token_t::RETURN: { ret = "RETURN"; break; }
    case token_t::CLASS: { ret = "CLASS"; break; }
    case token_t::INHERIT: { ret = "INHERIT"; break; }
    case token_t::PUBLIC: { ret = "PUBLIC"; break; }
    case token_t::PRIVATE: { ret = "PRIVATE"; break; }
    case token_t::PROTECTED: { ret = "PROTECTED"; break; }
    case token_t::VIRTUAL: { ret = "VIRTUAL"; break; }
    case token_t::OVERRIDE: { ret = "OVERRIDE"; break; }
    case token_t::INT: { ret = "INT"; break; }
    case token_t::FLOAT: { ret = "FLOAT"; break; }
    case token_t::HEX_INT: { ret = "HEX_INT"; break; }
    case token_t::DSTR: { ret = "DSTR"; break; }
    case token_t::STR: { ret = "STR"; break; }
    case token_t::R_DSTR: { ret = "R_DSTR"; break; }
    case token_t::R_STR: { ret = "R_STR"; break; }
    case token_t::F_DSTR: { ret = "F_DSTR"; break; }
    case token_t::F_STR: { ret = "F_STR"; break; }
    case token_t::RF_DSTR: { ret = "RF_DSTR"; break; }
    default:
        ret = "__UNKNOWN.TOKEN__";
    }
    return ret;
}
void LTEST::run(std::ostream &osm, const std::string_view& path)
{
    class frontend::Lexer lex {path};
    frontend::Token tk;
    unsigned char c_unk = 0;
    do {
        tk = lex.next();
        osm << "<" << LTEST::to_string(tk.type) << ">:<" << tk.value << ">\n";
        if (tk.type == frontend::token_t::UNKNOWN)
            ++c_unk;
    } while(tk.type != frontend::token_t::EOF_FILE && c_unk < 3);
}