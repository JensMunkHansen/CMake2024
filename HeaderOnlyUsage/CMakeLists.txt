cmake_minimum_required(VERSION 3.7)

project(mylibUsage VERSION 0.1 LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../HeaderOnly/build")

find_package(mylib CONFIG REQUIRED)
add_executable(MyApp main.cxx)
target_link_libraries(MyApp mylib)
