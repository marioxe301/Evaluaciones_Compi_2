#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H



enum class Token{
    Decimal,
    Hex,
    Binary,
    Octal,
    Eof,
    Error
};

Token getNextToken();
extern char*yytext;

#endif
