cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


PROJECT(ViennaMath)


set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

#SET(CMAKE_VERBOSE_MAKEFILE ON)   #uncomment this line to increase CMake verbosity

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(ViennaMathCommon)

#specify include directory
INCLUDE_DIRECTORIES(".")


# Set release build:
IF(DEFINED CMAKE_BUILD_TYPE)
 SET (CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
ELSE()
 SET (CMAKE_BUILD_TYPE Release)
ENDIF()

option(BUILD_TESTING "Build the tests" ON)

option(ENABLE_PEDANTIC_FLAGS "Enable pedantic compiler flags" ON)

cmake_dependent_option(ENABLE_DIST "Enable the the distribution tarball target" ON "BUILD_DOXYGEN_DOCS;BUILD_MANUAL" OFF)

mark_as_advanced(BUILD_DOXYGEN_DOCS BUILD_MANUAL ENABLE_DIST)

# Subdirectories
################

if(BUILD_EXAMPLES)
   add_subdirectory(examples)
endif()

if(BUILD_TESTING)
   include(CTest)
   add_subdirectory(tests)
endif()

add_subdirectory(doc)

# Install
#########

install(DIRECTORY viennamath ${CMAKE_CURRENT_BINARY_DIR}/viennamath
   DESTINATION ${INSTALL_INCLUDE_DIR} COMPONENT dev
   FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

##Compatibility with Qt-Creator
file( GLOB_RECURSE QtCreatorCompatibility_SRC
    viennamath/*.hpp viennamath/*.h)
add_custom_target( QtCreatorCompatibility SOURCES ${QtCreatorCompatibility_SRC} )


# packaging:
option(ENABLE_DIST "Enable the the distribution tarball target" ON)
mark_as_advanced(ENABLE_DIST)

if(ENABLE_DIST)
   file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/dist")

   set(DISTDIR "${PROJECT_BINARY_DIR}/dist/ViennaMath-${VERSION}")
   configure_file(cmake/CMakeLists.txt.in "${DISTDIR}/CMakeLists.txt" @ONLY)

   #
   # Full package:
   #
   add_custom_target(dist
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${DISTDIR}"

      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/LICENSE" "${DISTDIR}/LICENSE"

      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/README" "${DISTDIR}/README"

      COMMAND "${CMAKE_COMMAND}" -E make_directory "${DISTDIR}/build"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/build/README" "${DISTDIR}/build/README"

      COMMAND "${CMAKE_COMMAND}" -E make_directory "${DISTDIR}/doc"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/doc/viennamath.pdf" "${DISTDIR}/doc/viennamath.pdf"
      COMMAND "${CMAKE_COMMAND}" -E copy_directory
         "${PROJECT_SOURCE_DIR}/doc/doxygen"
         "${DISTDIR}/doc/doxygen"

      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/doc/Doxyfile" "${DISTDIR}/doc/Doxyfile"

      COMMAND "${CMAKE_COMMAND}" -E copy_directory
         "${PROJECT_SOURCE_DIR}/examples" "${DISTDIR}/examples"

      COMMAND "${CMAKE_COMMAND}" -E make_directory "${DISTDIR}/tests"
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${DISTDIR}/tests/src"
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${DISTDIR}/tests/data"
      COMMAND "${CMAKE_COMMAND}" -E copy_directory
         "${PROJECT_SOURCE_DIR}/tests/src" "${DISTDIR}/tests/src"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/tests/clean.sh" "${DISTDIR}/tests/clean.sh"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/tests/CMakeLists.txt" "${DISTDIR}/tests/CMakeLists.txt"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/tests/CTestConfig.cmake" "${DISTDIR}/tests/CTestConfig.cmake"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
         "${PROJECT_SOURCE_DIR}/tests/run_regression.sh" "${DISTDIR}/tests/run_regression.sh"

      COMMAND "${CMAKE_COMMAND}" -E copy_directory
         "${PROJECT_SOURCE_DIR}/viennamath" "${DISTDIR}/viennamath"

      COMMAND "${CMAKE_COMMAND}" -E tar czf ViennaMath-${VERSION}.tar.gz
           ViennaMath-${VERSION}
      WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/dist"
      COMMENT "Generating dist/ViennaMath-${VERSION}.tar.gz"
      VERBATIM)

endif()


