%define parse.error verbose
%parse-param{ std::unordered_map<std::string,int>& vars }
%parse-param{ std::ostringstream& sout }

%code requires {

#include <unordered_map>
#include <sstream>
#include <string>

}

%{
#include <sstream>
#include <unordered_map>
#include <string>
#include "expr_lexer.h"

extern ExprLexer yylex;

void yyerror(std::unordered_map<std::string,int>& vars,std::ostringstream& sout,const char* msj){
    throw std::string(msj);
}
%}

%token<str_t> IDENT "id"
%token<number_t> NUMBER "num"
%token OPEN_PAR "("
%token CLOSE_PAR ")"
%token OPADD "+"
%token OPMUL "*"
%token EOL
%token TKEOF
%token OPASSIGN "="
%token KWPRINT "print"

%union {
    int number_t;
    char *str_t;
}

%type<number_t> expr term fact

%%

input: stmts eolist
    ;

eolist: EOL | %empty
    ;

stmts: stmts EOL stmt | stmt
    ;

stmt: "print" expr { sout<< std::to_string($2) << '\n'; } | "id" "=" expr { vars.emplace($1, $3); }
    ;

expr: expr "+" term { $$ = $1 + $3; }
    | term { $$ = $1;}
    ;

term: term "*" fact { $$ = $1 * $3; } 
    | fact { $$ = $1;}
    ;

fact: "num" { $$ = $1;} 
    | "(" expr ")" { $$ = $2 ;}
    | "id" { std::string ident =  $1; $$ = vars.at(ident) ; free($1); }
    ;
%%
