
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(FooApp FooApp.cxx)
set_target_properties(FooApp PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(FooApp PUBLIC Foo build)

#set_target_properties(FooApp PROPERTIES INSTALL_RPATH_USE_LINK_PATH

install(TARGETS FooApp
  EXPORT ${PROJECT_NAME}Targets
  DESTINATION bin
  RUNTIME DESTINATION "${CMAKE_INSTALL_BIN_DIR}"
          COMPONENT ${PROJECT_NAME}_Runtime
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIB_DIR}"
          COMPONENT ${PROJECT_NAME}_Devel
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIB_DIR}"
          COMPONENT ${PROJECT_NAME}_Devel
	  NAMELINK_COMPONENT ${PROJECT_NAME}_Devel
)

