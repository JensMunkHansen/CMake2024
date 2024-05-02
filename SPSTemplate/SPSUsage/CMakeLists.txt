cmake_minimum_required(VERSION 3.23)

project(SPSUsage VERSION 0.8 LANGUAGES CXX)

# We require pure CONFIG mode (don't look into the old Modules folder)
find_package(SPSFunctional 0.1 EXACT CONFIG)
if (NOT SPSFunctional_FOUND)
  message(FATAL_ERROR "We cannot find the library")
endif()
add_executable(MyApp main.cxx)

# Here we link public (not interface) and thereby enforce
# the same flags
target_link_libraries(MyApp PUBLIC SPS::SPSFunctional)
