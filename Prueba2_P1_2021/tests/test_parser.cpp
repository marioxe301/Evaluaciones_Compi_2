#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <unordered_map>
#include "doctest.h"
#include "expr_lexer.h"

ExprLexer yylex;

std::vector<TokenInfo> error = {
    std::make_pair(IDENT, "x"),
    std::make_pair(TKEOF, "TKEOF")
};

std::vector<TokenInfo> assign = {
    std::make_pair(IDENT, "x"),
    std::make_pair(OPASSIGN, "="),
    std::make_pair(OPEN_PAR, "("),
    std::make_pair(NUMBER, "10"),
    std::make_pair(OPADD, "+"),
    std::make_pair(NUMBER, "7"),
    std::make_pair(CLOSE_PAR, ")"),
    std::make_pair(OPMUL, "*"),
    std::make_pair(NUMBER, "5"),
    std::make_pair(EOL, "\\n"),
    std::make_pair(TKEOF, "TKEOF")
};

std::vector<TokenInfo> print = {
    std::make_pair(KWPRINT, "print"),
    std::make_pair(OPEN_PAR, "("),
    std::make_pair(NUMBER, "10"),
    std::make_pair(OPADD, "+"),
    std::make_pair(NUMBER, "7"),
    std::make_pair(CLOSE_PAR, ")"),
    std::make_pair(OPMUL, "*"),
    std::make_pair(NUMBER, "5"),
    std::make_pair(EOL, "\\n"),
    std::make_pair(TKEOF, "TKEOF")
};

std::vector<TokenInfo> multiple = {
    std::make_pair(IDENT, "x"),
    std::make_pair(OPASSIGN, "="),
    std::make_pair(OPEN_PAR, "("),
    std::make_pair(NUMBER, "10"),
    std::make_pair(OPADD, "+"),
    std::make_pair(NUMBER, "7"),
    std::make_pair(CLOSE_PAR, ")"),
    std::make_pair(OPMUL, "*"),
    std::make_pair(NUMBER, "5"),
    std::make_pair(EOL, "\\n"),
    std::make_pair(KWPRINT, "print"),
    std::make_pair(IDENT, "x"),
    std::make_pair(TKEOF, "TKEOF")
};

bool throwOnError() 
{
    yylex.setTokenList(error);
    
    bool throwException = false;
    try {
        std::unordered_map<std::string, int> vars;
        std::ostringstream sout;

        yyparse(vars, sout);
    } catch (...) {
        throwException = true;
    }
    return throwException;
}

TEST_CASE("Assign statement") {
    REQUIRE(throwOnError());
    std::unordered_map<std::string, int> vars;
    std::ostringstream sout;

    sout.str("");
    yylex.setTokenList(assign);

    bool parseSuccess = false;
    try {
        yyparse(vars, sout);
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);
    CHECK(vars["x"] == 85);
    CHECK(sout.str().empty());
}

TEST_CASE("Print statement") {
    REQUIRE(throwOnError());
    std::unordered_map<std::string, int> vars;
    std::ostringstream sout;

    sout.str("");
    yylex.setTokenList(print);

    bool parseSuccess = false;
    try {
        yyparse(vars, sout);
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);
    CHECK(sout.str() == "85\n");
}

TEST_CASE("Assign/Print") {
    REQUIRE(throwOnError());
    std::unordered_map<std::string, int> vars;
    std::ostringstream sout;

    sout.str("");
    yylex.setTokenList(multiple);

    bool parseSuccess = false;
    try {
        yyparse(vars, sout);
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);
    CHECK(vars["x"] == 85);
    CHECK(sout.str() == "85\n");
}
