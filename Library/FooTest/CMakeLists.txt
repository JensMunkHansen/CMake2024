if(NOT BUILD_TESTING)
  return()
endif()

add_cpp_test(foo_test.cxx)
target_link_libraries(foo_test PUBLIC Foo)
