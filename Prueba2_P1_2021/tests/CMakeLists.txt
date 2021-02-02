cmake_minimum_required (VERSION 2.6)
project (test_parser)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14" )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)

# Run bison to generate the parser
add_custom_command (
  OUTPUT expr_parser.cpp expr_tokens.h
  COMMAND bison -o expr_parser.cpp -rall --defines=expr_tokens.h ${PROJECT_SOURCE_DIR}/../expr.y
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../expr.y
  )
  
add_executable(${PROJECT_NAME}  expr_parser.cpp
                                test_parser.cpp)

enable_testing()
add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME})
