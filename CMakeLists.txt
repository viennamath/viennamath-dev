
PROJECT(viennamath)

cmake_minimum_required(VERSION 2.6)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

#specify include directory
#INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/viennama")
INCLUDE_DIRECTORIES(".")

#add definitions, compiler switches, etc.
#ADD_DEFINITIONS(-Wall -pedantic -O3)
ADD_DEFINITIONS(-Wall -pedantic -O0 -g)

# examples:
ADD_EXECUTABLE(basic                examples/basic.cpp)
ADD_EXECUTABLE(integration          examples/integration.cpp)
ADD_EXECUTABLE(latex_output         examples/latex_output.cpp)
ADD_EXECUTABLE(model_benchmark      examples/model_benchmark.cpp)
ADD_EXECUTABLE(newton_solve         examples/newton_solve.cpp)
ADD_EXECUTABLE(traversal            examples/traversal.cpp)
ADD_EXECUTABLE(substitute           examples/substitute.cpp)
ADD_EXECUTABLE(vector_expr          examples/vector_expr.cpp)

 
