cmake_minimum_required (VERSION 2.6)
project (test_parser)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14" )

# Run bison to generate the parser
add_custom_command (
  OUTPUT expr_parser.cpp expr_parser.h
  COMMAND bison -o expr_parser.cpp --defines=expr_tokens.h ${PROJECT_SOURCE_DIR}/../expr_parser.y
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../expr_parser.y
  )

# Run flex to generate the lexer
add_custom_command (
  OUTPUT expr_lexer.cpp
  COMMAND flex -o expr_lexer.cpp ${PROJECT_SOURCE_DIR}/../expr_lexer.l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../expr_lexer.l
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(test_parser  expr_parser.cpp
                            expr_lexer.cpp
                            test_parser.cpp)

enable_testing()
add_test(NAME test_parser
         COMMAND test_parser)
