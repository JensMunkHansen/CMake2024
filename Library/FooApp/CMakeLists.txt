add_executable(FooApp FooApp.cxx)
set_target_properties(FooApp PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(FooApp PUBLIC Foo)
