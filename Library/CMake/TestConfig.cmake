include(CTest)
include(GoogleTest) # CMake macros for GoogleTest
find_package(GTest)
if (NOT GTest_FOUND)
  set(BUILD_TESTING OFF)
  return()
endif()
enable_testing()

# add_cpp_test()
# CMake function to generate and build C++ test.
# Parameters:
#  the C++ filename
# e.g.:
# add_cpp_test(foo.cpp)
function(add_cpp_test FILE_NAME)
  message(STATUS "Configuring test ${FILE_NAME}: ...")
  get_filename_component(TEST_NAME ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME} NAME_WE)

  if(APPLE)
    set(CMAKE_INSTALL_RPATH
      "@loader_path/../${CMAKE_INSTALL_LIBDIR};@loader_path")
  elseif(UNIX)
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}:$ORIGIN")
  endif()

  add_executable(${TEST_NAME} ${FILE_NAME})
  # alternative, which also populates the test list
  # gtest_add_tests(TARGET ${TEST_NAME})
  target_link_libraries(${TEST_NAME}
    PRIVATE
    GTest::gtest_main)

  target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)
  gtest_discover_tests(${TEST_NAME}) # adds the test again
endfunction()
