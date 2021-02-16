%language "c++"
%define parse.error verbose
%define api.value.type variant
%define api.parser.class{ Parser }
%define api.namespace{ Expr }

%parse-param{ std::unordered_map<std::string,int> &vars }
%parse-param{ std::vector<int>& res }

%code requires {
    #include <unordered_map>
    #include <string>
    #include <vector>
}

%{
#include <string>
#include <unordered_map>
#include <vector>
#include "expr_tokens.h"

int yylex(Expr::Parser::semantic_type *yylval);

namespace Expr{
    void Parser::error(const std::string&msj){
        throw msj;
    }
}

%}

%token Add Sub Mult Div Mod
%token OpenPar ClosePar
%token<std::string> Identifier
%token<int> Number
%token EoL
%token Error
%token SemiColon

%type<int> expr term fact


%%

program: expr_list
    ;

expr_list: expr_list expr opt_semicolon  { res.push_back($2); }
    | expr opt_semicolon { res.push_back($1); }
    ;

opt_semicolon: SemiColon 
    | %empty
    ;

expr: expr Add term { $$ = $1 + $3;}
    | expr Sub term { $$ = $1 - $3;}
    | term { $$ = $1;}
    ;

term: term Mult fact {  $$ = $1 * $3; }
    | term Div fact { $$ = $1 / $3;}
    | term Mod fact { $$ = $1 % $3;}
    | fact { $$ = $1;}
    ;

fact: Number { $$ = $1;}
    | OpenPar expr ClosePar { $$ = $2; }
    | Identifier{ $$ = vars[$1]; }
    ;

%%