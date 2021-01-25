cmake_minimum_required (VERSION 2.6)
project (test_expr_lexer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14")

# Run flex to generate the lexer
add_custom_command (
  OUTPUT expr_lexer.cpp
  COMMAND flex -o expr_lexer.cpp ${PROJECT_SOURCE_DIR}/../expr.l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../expr.l
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/..)
 
add_executable(${PROJECT_NAME} expr_lexer.cpp test_lexer.cpp)

