%option noyywrap

%{

#include "expr_lexer.h"
#include <string>
#define yyterminate() return Token::Eof
#define YY_DECL Token getNextToken()

%}

DECIMAL [0-9]+
HEX 0x[0-9a-f]+
BINARY 0b[0-1]+
OCTAL 0[1-7]{1}[0-7]*



%%

{HEX}   return Token::Hex;
{BINARY} return Token::Binary;
{OCTAL} return Token::Octal;
{DECIMAL} return Token::Decimal;
[ ] /* Ignorar espacios*/
. throw std::string("Error Inesperado");

%%