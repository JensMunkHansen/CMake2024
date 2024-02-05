cmake_minimum_required(VERSION 3.15)

project(LibraryUsage
  VERSION 1.0.0
  LANGUAGES CXX)

find_package(Foo REQUIRED)

add_executable(FooUsage main.cxx)
target_link_libraries(FooUsage PRIVATE Foo)
