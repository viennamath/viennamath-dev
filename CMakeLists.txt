
PROJECT(viennamath)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

#specify include directory
#INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/viennama")

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

#list all source files here
ADD_EXECUTABLE(test examples/test.cpp)

#need to link to some other libraries ? just add them here
#TARGET_LINK_LIBRARIES(quantitymanager png jpeg)
 
