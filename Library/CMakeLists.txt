cmake_minimum_required(VERSION 3.15)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# set the project name and version
project(Library
  LANGUAGES CXX
  VERSION 1.0.0)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include(BuildConfig)
include(CompilerFlags)

add_subdirectory(Foo)

add_subdirectory(FooApp)

# install the configuration targets
install(EXPORT FooTargets
  FILE FooTargets.cmake
  DESTINATION lib/cmake/Foo
)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/FooConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/FooConfigVersion.cmake"
  VERSION "${Library_VERSION_MAJOR}.${Library_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

# install the configuration file
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/FooConfig.cmake
  DESTINATION lib/cmake/Foo
  )

# generate the export targets for the build tree
# needs to be after the install(TARGETS ) command
export(EXPORT FooTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/FooTargets.cmake"
)
