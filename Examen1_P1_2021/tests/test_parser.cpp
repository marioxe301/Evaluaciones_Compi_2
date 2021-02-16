#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <vector>
#include <sstream>
#include "doctest.h"
#include "expr_tokens.h"
#include "expr_lexer.h"

/* 1 */ std::string test_add = "45 + 10 # Add expression";
/* 1 */ std::string test_sub = "45 - 10; # Sub expression";
/* 1 */ std::string test_mul = "45 * 9 # Mult expression";
/* 1 */ std::string test_div = "45 / 7; # Div expression";
/* 1 */ std::string test_mod = "45 % 7 # Mod expression";

/* 2 */ std::string test_vars = "(variable1 + var_2) * multiplier;";

/* 3 */ std::string test_multiple = "(53 + 35 ) * 100; {Expression 1}\n"
                            "(43 + 65) / 4; {Expression 2}\n"
                            "(variable1 - var_2) % divisor # Last expression";

TEST_CASE("Add operation")
{
    std::unordered_map<std::string, int> vars;
    std::vector<int> values;

    YY_BUFFER_STATE input = yy_scan_string(test_add.c_str());
    yy_switch_to_buffer(input);
    Expr::Parser parser(vars, values);

    parser();
    yy_delete_buffer(input);
    
    CHECK(values.size() == 1);
    CHECK(values[0] == 55);
}

TEST_CASE("Sub operation")
{
    std::unordered_map<std::string, int> vars;
    std::vector<int> values;

    YY_BUFFER_STATE input = yy_scan_string(test_sub.c_str());
    yy_switch_to_buffer(input);
    Expr::Parser parser(vars, values);

    parser();
    yy_delete_buffer(input);

    CHECK(values.size() == 1);
    CHECK(values[0] == 35);
}

TEST_CASE("Mult operation")
{
    std::unordered_map<std::string, int> vars;
    std::vector<int> values;

    YY_BUFFER_STATE input = yy_scan_string(test_mul.c_str());
    yy_switch_to_buffer(input);
    Expr::Parser parser(vars, values);

    parser();
    yy_delete_buffer(input);

    CHECK(values.size() == 1);
    CHECK(values[0] == 405);
}

TEST_CASE("Div operation")
{
    std::unordered_map<std::string, int> vars;
    std::vector<int> values;

    YY_BUFFER_STATE input = yy_scan_string(test_div.c_str());
    yy_switch_to_buffer(input);
    Expr::Parser parser(vars, values);

    parser();
    yy_delete_buffer(input);

    CHECK(values.size() == 1);
    CHECK(values[0] == 6);
}

TEST_CASE("Mod operation")
{
    std::unordered_map<std::string, int> vars;
    std::vector<int> values;

    YY_BUFFER_STATE input = yy_scan_string(test_mod.c_str());
    yy_switch_to_buffer(input);
    Expr::Parser parser(vars, values);

    parser();
    yy_delete_buffer(input);
    
    CHECK(values.size() == 1);
    CHECK(values[0] == 3);
}

TEST_CASE("Expression with variables")
{
    std::unordered_map<std::string, int> vars;
    std::vector<int> values;
    
    YY_BUFFER_STATE input = yy_scan_string(test_vars.c_str());
    yy_switch_to_buffer(input);
    Expr::Parser parser(vars, values);

    vars["variable1"] = 37;
    vars["var_2"] = 23;
    vars["multiplier"] = 91;
    
    parser();
    yy_delete_buffer(input);

    CHECK(values.size() == 1);
    CHECK(values[0] == 5460);
}

TEST_CASE("Multiple expressions")
{
    std::unordered_map<std::string, int> vars;
    std::vector<int> values;

    YY_BUFFER_STATE input = yy_scan_string(test_multiple.c_str());
    yy_switch_to_buffer(input);
    Expr::Parser parser(vars, values);

    vars["variable1"] = 97;
    vars["var_2"] = 22;
    vars["divisor"] = 37;
    
    parser();
    yy_delete_buffer(input);

    CHECK(values.size() == 3);
    CHECK(values[0] == 8800);
    CHECK(values[1] == 27);
    CHECK(values[2] == 1);
}
