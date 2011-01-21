
PROJECT(viennamath)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

#specify include directory
#INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/viennama")
INCLUDE_DIRECTORIES(".")

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -pedantic -O3)
#ADD_DEFINITIONS(-Wall -pedantic -O0 -g)

#list all source files here
ADD_EXECUTABLE(basic_test examples/basic_test.cpp)
ADD_EXECUTABLE(runtime_test examples/runtime_test.cpp)
ADD_EXECUTABLE(compiletime_test examples/compiletime_test.cpp)
ADD_EXECUTABLE(compiletime_evaluation examples/compiletime_evaluation.cpp)
ADD_EXECUTABLE(model_benchmark examples/model_benchmark.cpp)

 
