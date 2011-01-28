
PROJECT(viennamath)

cmake_minimum_required(VERSION 2.6)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

#specify include directory
#INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/viennama")
INCLUDE_DIRECTORIES(".")

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -pedantic -O3)
#ADD_DEFINITIONS(-Wall -pedantic -O0 -g)

# examples:
ADD_EXECUTABLE(basic_test examples/basic_test.cpp)
ADD_EXECUTABLE(model_benchmark examples/model_benchmark.cpp)
ADD_EXECUTABLE(newton_solve examples/newton_solve.cpp)

# tests:
ADD_EXECUTABLE(runtime_test tests/runtime_test.cpp)
ADD_EXECUTABLE(compiletime_test tests/compiletime_test.cpp)
ADD_EXECUTABLE(compiletime_evaluation tests/compiletime_evaluation.cpp)
ADD_EXECUTABLE(diff_test tests/diff_test.cpp)
ADD_EXECUTABLE(equation_test tests/equation_test.cpp)
 
