# TODO: Runtime-path not set correctly...

cmake_minimum_required(VERSION 3.15)

project(DeepLibraryLargeUsage
  VERSION 1.0.0
  LANGUAGES CXX)

find_package(Deep REQUIRED)

add_executable(DeepLibraryLargeUsage main.cxx)
target_link_libraries(DeepLibraryLargeUsage PRIVATE Deep)
