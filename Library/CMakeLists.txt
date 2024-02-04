cmake_minimum_required(VERSION 3.15)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# set the project name and version
project(Library
  LANGUAGES CXX
  VERSION 1.0.0)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include(BuildConfig)
include(CompilerFlags)

add_subdirectory(Foo)

add_subdirectory(FooApp)

# install the configuration targets
install(EXPORT FooTargets
  FILE FooTargets.cmake
  DESTINATION lib/cmake/Foo
)

#export(EXPORT FooTargets
#  FILE "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsTargets.cmake"
#)
