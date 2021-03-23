#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "doctest.h"
#include "spl_ast.h"

#include "ast_nodes.h"

std::string runCmd(const std::string& cmd)
{
    FILE *stream = popen( cmd.c_str(), "r" );
    REQUIRE (stream != nullptr);

    std::ostringstream ssdata;
    char buffer[256] = {0};

    while(fgets(buffer, sizeof(buffer) - 1, stream))
        ssdata << buffer;

    return ssdata.str();
}

std::string runAsm(const char *filename, const std::string& code)
{
    std::string asm_file = std::string(filename) + ".asm";
    std::string obj_file = std::string(filename) + ".o";

    std::ofstream out(asm_file, std::ios::out|std::ios::trunc);

    REQUIRE (out.is_open());
    out << code << "\n";
    out.close();

    std::string cmd = std::string("nasm -felf32 ") + asm_file + " 2>&1";
    std::string output = runCmd(cmd);

    REQUIRE(output.empty());

    cmd = std::string("gcc -m32 -o ") + filename + " " + obj_file + " 2>&1";
    output = runCmd(cmd);

    REQUIRE(output.empty());

    cmd = std::string("./") + filename;
    return runCmd(cmd);
}

TEST_CASE("Bitwise operators")
{
    Ast::Program *prg = Prg({
            Func(
                "main",
                {},
                Block({
                    Print(And(Var("x"), Var("y"))),
                    Print(Or(Var("x"), Var("y"))),
                    Print(Xor(Var("x"), Var("y"))),
                })
            )
        });

    {
        SymbolVector symbs { {"x", 14598366}, {"y", 0xffff00}};
        std::string code = prg->genProgramCode(symbs);

        std::string output = runAsm("bitwise", code);

        CHECK(output == "14598144167771822179038");
    }
}

TEST_CASE("If statement")
{
    Ast::Program *prg = Prg({
            Func(
                "main",
                {},
                If(Var("x"), Print(Var("y")), Print(Var("z")))
            )
        });

    {
        SymbolVector symbs { {"x", 1}, {"y", 1234}, {"z", 4321}};
        std::string code = prg->genProgramCode(symbs);

        std::string output = runAsm("if1", code);

        CHECK(output == "1234");
    }

    {
        SymbolVector symbs { {"x", 0}, {"y", 1234}, {"z", 4321}};
        std::string code = prg->genProgramCode(symbs);

        std::string output = runAsm("if1", code);

        CHECK(output == "4321");
    }
}

TEST_CASE("While statement")
{
    Ast::Program *prg = Prg({
            Func(
                "main",
                {},
                While(LessThan(Var("x"), Num(5)),
                      Block({
                          Assign("x", Add(Var("x"), Num(1))),
                          Print(Var("x"))
                      }))
            )
        });

    SymbolVector symbs { {"x", 0}};
    std::string code = prg->genProgramCode(symbs);

    std::string output = runAsm("while", code);

    CHECK(output == "12345");
}

TEST_CASE("Call statement by value")
{
    Ast::Program *prg = Prg({
            Func(
                "main",
                {},
                Call("Add", {Var("a"), Var("b")})
            ),
            Func(
                "Add",
                { ParamByVal("x"), ParamByVal("y") },
                Print(Add(Var("x"), Var("y")))
            )
        });
    
    SymbolVector symbs { {"a", 125}, {"b", 340}};
    std::string code = prg->genProgramCode(symbs);

    std::string output = runAsm("callv", code);

    CHECK(output == "465");
}

TEST_CASE("Call statement by reference 1")
{
    Ast::Program *prg = Prg({
            Func(
                "main",
                {},
                Block({
                    Call("Add", { Var("a"), Var("b"), Var("c") }),
                    Print(Var("c"))
                })
            ),
            Func(
                "Add",
                { ParamByVal("x"), ParamByVal("y"), ParamByRef("z") },
                Assign("z", Add(Var("x"), Var("y")))
            )
        });

    SymbolVector symbs { {"a", 125}, {"b", 340}, {"c", 777} };
    std::string code = prg->genProgramCode(symbs);

    std::string output = runAsm("callr1", code);

    CHECK(output == "465");
}

TEST_CASE("Call statement by reference 2")
{
    Ast::Program *prg = Prg({
            Func(
                "main",
                {},
                Block({
                    Call("add1", { Var("a"), Var("b"), Var("c") }),
                    Print(Var("c"))
                })
            ),
            Func(
                "add1",
                { ParamByVal("x"), ParamByVal("y"), ParamByRef("z") },
                Call("add2", {Var("x"), Var("y"), Var("z")})
            ),
            Func(
                "add2",
                { ParamByVal("x"), ParamByVal("y"), ParamByRef("z") },
                Assign("z", Add(Var("x"), Var("y")))
            )
        });
    
    SymbolVector symbs { {"a", 125}, {"b", 340}, {"c", 777} };
    std::string code = prg->genProgramCode(symbs);

    std::string output = runAsm("callr2", code);

    CHECK(output == "465");
}

TEST_CASE("Call statement by reference 3")
{
    Ast::Program *prg = Prg({
            Func(
                "main",
                {},
                Call("add1", {Var("a"), Var("b"), Var("c")})
            ),
            Func(
                "add1",
                { ParamByVal("x"), ParamByVal("y"), ParamByRef("z") },
                Block({
                    Call("add2", {Var("x"), Var("y"), Var("z")}),
                    Print(Var("z"))
                })
            ),
            Func(
                "add2",
                { ParamByVal("x"), ParamByVal("y"), ParamByRef("z") },
                Assign("z", Add(Var("x"), Var("y")))
            )
        });
    
    SymbolVector symbs { {"a", 125}, {"b", 340}, {"c", 777} };
    std::string code = prg->genProgramCode(symbs);

    std::string output = runAsm("callr3", code);

    CHECK(output == "465");
}