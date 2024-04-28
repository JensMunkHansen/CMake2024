cmake_minimum_required(VERSION 3.23...3.26)

project(Artifactory
  LANGUAGES CXX
  VERSION 0.9.0)

# Here we use Catch2 (statically)
include(ExternalProject)

# Google's test framework
ExternalProject_Add(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2 # or a later release
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DBUILD_SHARED_LIBS=OFF)

