cmake_minimum_required(VERSION 3.23...3.26)

project(Artifactory)

# Here we use Catch2 (dynamically)
include(ExternalProject)

# Google's test framework
ExternalProject_Add(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2 # or a later release
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR} -DBUILD_SHARED_LIBS=ON)

