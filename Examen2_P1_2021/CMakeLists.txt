cmake_minimum_required (VERSION 3.8)
project(test_spl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(TreeCC REQUIRED)

add_custom_command(
  OUTPUT spl_ast.cpp spl_ast.h
  COMMAND ${TREECC} -o spl_ast.cpp ${PROJECT_SOURCE_DIR}/spl_ast.tc
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/spl_ast.tc
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} spl_ast.cpp test_spl.cpp)
