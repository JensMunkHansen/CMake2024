cmake_minimum_required(VERSION 3.15)

project(LibraryUsage
  VERSION 1.0.0
  LANGUAGES CXX)

# TODO: Figure out how to avoid this
list(APPEND CMAKE_PREFIX_PATH "/home/jmh/github/cmake/CMake2024/Library/build")

find_package(Foo REQUIRED)

add_executable(FooUsage main.cxx)
target_link_libraries(FooUsage PRIVATE Foo)
