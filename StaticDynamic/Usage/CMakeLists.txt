cmake_minimum_required(VERSION 3.23...3.26)

project(StackFunctionUsage
  LANGUAGES CXX
  VERSION 0.9.0)

# Configure Catch2 [external project] with BUILD_SHARED_LIBS=ON
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/deps)
execute_process(
    COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR}/deps
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/deps)
execute_process(
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/deps)

find_package(StackFunction REQUIRED)
find_package(Catch2 3.5.3 EXACT REQUIRED PATHS "${PROJECT_BINARY_DIR}/deps/lib/cmake" NO_DEFAULT_PATHS)

if (NOT Catch2_FOUND)
  set(BUILD_TESTING OFF)
  message(WARNING "Tests disabled")
  return()
endif()

enable_testing()

set(TEST_NAME usageTest)
add_executable(usageTest usageTest.cxx)
target_link_libraries(${TEST_NAME} PUBLIC StackFunction)
target_link_libraries(${TEST_NAME} PUBLIC Catch2::Catch2)
target_link_libraries(${TEST_NAME} PUBLIC Catch2::Catch2WithMain) # Catch2 v3
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})


if (MSVC)
  add_custom_command( TARGET ${TEST_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_RUNTIME_DLLS:${TEST_NAME}>
    $<TARGET_FILE_DIR:${TEST_NAME}>
    COMMAND_EXPAND_LISTS)
endif()

