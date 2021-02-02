#ifndef _ExprLexer_H
#define _ExprLexer_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "expr_tokens.h"

using TokenInfo = std::pair<int, std::string>;

#define TKEOF 0

class ExprLexer
{
public:
    ExprLexer() {}

    void setTokenList(const std::vector<TokenInfo>& tklst)
    {
        tklist = tklst;
        it = tklist.begin();
    }

    int getLineNo() { return 1; }

    int operator()()
    {
        int tk = it->first;

        if (tk == NUMBER)
            yylval.number_t = std::strtol(it->second.c_str(), nullptr, 10);
        else
            yylval.str_t = strdup(it->second.c_str());

        if (it != tklist.end())
            it++;

        return tk;
    }

    bool hasTokens() { return it != tklist.end(); }

private:
    int intVal;
    std::string strVal;
    std::vector<TokenInfo> tklist;
    std::vector<TokenInfo>::iterator it;
};
#endif
