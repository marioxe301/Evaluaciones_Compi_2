#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <sstream>
#include "doctest.h"
#include "expr_lexer.h"

struct yy_buffer_state;
using YY_BUFFER_STATE = yy_buffer_state *;

YY_BUFFER_STATE yy_scan_string(const char *yy_str);
void yy_switch_to_buffer(YY_BUFFER_STATE new_buffer);

extern char *yytext;

const char *test = "0xdeadbeef 12345678 0 0b1010 07654 a";

doctest::String toString(Token tk)
{
    switch (tk) {
        case Token::Decimal: return "Decimal";
        case Token::Hex: return "Hex";
        case Token::Binary: return "Binary";
        case Token::Octal: return "Octal";
        case Token::Eof: return "Eof";
        default:
            return "Unknown";
    }
}

TEST_CASE("Lexer")
{
    YY_BUFFER_STATE bs = yy_scan_string(test);
    yy_switch_to_buffer(bs);

    Token tk = getNextToken();
    std::string text = yytext;
    
    CHECK(tk == Token::Hex);
    CHECK(text == "0xdeadbeef");
    
    tk = getNextToken();
    text = yytext;
    CHECK(tk == Token::Decimal);
    CHECK(text == "12345678");
    
    tk = getNextToken();
    text = yytext;
    CHECK(tk == Token::Decimal);
    CHECK(text == "0");
    
    tk = getNextToken();
    text = yytext;
    CHECK(tk == Token::Binary);
    CHECK(text == "0b1010");
    
    tk = getNextToken();
    text = yytext;
    CHECK(tk == Token::Octal);
    CHECK(text == "07654");
    
    try {
        tk = getNextToken();
        CHECK(false);
    } catch (std::string& s) {
        /* Nothing */
    }
    
    tk = getNextToken();
    CHECK(tk == Token::Eof);
}
