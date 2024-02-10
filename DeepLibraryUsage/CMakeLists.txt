# TODO: Runtime-path not set correctly...

cmake_minimum_required(VERSION 3.15)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

include(DumpVariables)

project(LibraryUsage
  VERSION 1.0.0
  LANGUAGES CXX)

find_package(Deep REQUIRED)

add_executable(DeepUsage main.cxx)
target_link_libraries(DeepUsage PUBLIC Deep)

# Utility function for dumping variables
dump_cmake_variables()
