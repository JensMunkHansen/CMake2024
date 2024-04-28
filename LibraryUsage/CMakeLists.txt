# TODO: Runtime-path not set correctly...

# FIND_LIBRARY_USE_LIB64_PATHS=1 => lib64 are searched

cmake_minimum_required(VERSION 3.23)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

project(LibraryUsage
  VERSION 1.0.0
  LANGUAGES CXX)

include(BuildConfig) # Not yet deploying DLL's correctly

find_package(Library2 REQUIRED)

find_package(Bar REQUIRED)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(FooUsage main.cxx)
set_target_properties(FooUsage PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

if (MSVC)
    add_custom_command( TARGET FooUsage POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      $<TARGET_RUNTIME_DLLS:FooUsage>
      $<TARGET_FILE_DIR:FooUsage>
      COMMAND_EXPAND_LISTS)
endif()

# TODO: Consider using namespace
#target_link_libraries(FooUsage PUBLIC algorithms)
target_link_libraries(FooUsage PUBLIC Foo)
target_link_libraries(FooUsage PUBLIC Bar) # Get the compile parameters (only if PUBLIC)

get_target_property(BUM algorithms INTERFACE_COMPILE_OPTIONS)
#target_link_libraries(FooUsage $<TARGET_FILE:algorithms> $<TARGET_PROPERTY:INTERFACE_LINK_LIBRARIES>)

# This will stop stripping rpath - but then it is not moveable

install(TARGETS FooUsage
  EXPORT FooUsageTargets
  DESTINATION bin
  RUNTIME DESTINATION "${CMAKE_INSTALL_BIN_DIR}"
          COMPONENT ${PROJECT_NAME}_Runtime
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIB_DIR}"
          COMPONENT ${PROJECT_NAME}_Devel
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIB_DIR}"
          COMPONENT ${PROJECT_NAME}_Devel
	  NAMELINK_COMPONENT ${PROJECT_NAME}_Devel)

# install the configuration targets
install(EXPORT FooUsageTargets
  FILE FooUsageTargets.cmake
  DESTINATION bin
)

#foreach(component ${@PROJECT_NAME@_FIND_COMPONENTS})
#    include(${CMAKE_CURRENT_LIST_DIR}/${component}-config.cmake)
#endforeach()


export(EXPORT FooUsageTargets
  #  NAMESPACE Foo:: # TODO: Figure out how to use namespaces
  FILE "${CMAKE_CURRENT_BINARY_DIR}/FooUsageTargets.cmake"
)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/FooUsageConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/FooUsage"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/FooUsageConfigVersion.cmake"
  VERSION "${LibraryUsage_VERSION_MAJOR}.${LibraryUsage_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

# setup installer using CPack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${LibraryUsage_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${LibraryUsage_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Packaging")

include(CPack)
