%option noyywrap

%{
#include <string>
#include "expr_tokens.h"

#define YY_DECL int yylex(Expr::Parser::semantic_type *yylval)
using TOKEN = Expr::Parser::token;

%}


NUMBER [0-9]+(\.[0-9]*)?
ID [_a-z]?[_a-z0-9]+
COMMENTS  [#][^\n]+

%x b_comments

%%
{COMMENTS} ;
\{ { BEGIN(b_comments);} 
{NUMBER} yylval->emplace<int>(atof(yytext)); return TOKEN::Number;
{ID} yylval->emplace<std::string>(yytext,yyleng); return TOKEN::Identifier;
\( return TOKEN::OpenPar;
\) return TOKEN::ClosePar;
\+ return TOKEN::Add;
\- return TOKEN::Sub;
\/ return TOKEN::Div;
\* return TOKEN::Mult;
\% return TOKEN::Mod;
\; return TOKEN::SemiColon;
[ \t\n] ;
<b_comments>\} { BEGIN(INITIAL);}
<b_comments>.|\n ;
. return TOKEN::Error;
%%