cmake_minimum_required(VERSION 3.15..3.27)

###################################################################################
# Set some CMake Policies.
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details.
###################################################################################
set(project_policies
  CMP090 # export to registry using CMAKE_EXPORT_PACKAGE_REGISTRY 
)
foreach(policy ${project_policies})
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# set the project name and version
project(Library
  LANGUAGES CXX
  VERSION 1.0.0)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include(target_public_headers)
include(BuildConfig)

include(CompilerFlags)

add_subdirectory(Foo)

add_subdirectory(FooApp)

# install the configuration targets
install(EXPORT FooTargets
  FILE FooTargets.cmake
  DESTINATION lib/cmake/Foo
)

# Enable writing to registry
set(CMAKE_EXPORT_PACKAGE_REGISTRY 1)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/FooConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/Foo"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/FooConfigVersion.cmake"
  VERSION "${Library_VERSION_MAJOR}.${Library_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

# install the configuration files
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/FooConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/FooConfigVersion.cmake
  DESTINATION lib/cmake/Foo
  COMPONENT dev
  )

# generate the export targets for the build tree
# needs to be after the install(TARGETS ) command
export(EXPORT FooTargets
  #  NAMESPACE Foo:: # TODO: Figure out how to use namespaces
  FILE "${CMAKE_CURRENT_BINARY_DIR}/FooTargets.cmake"
)

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE Foo)

if (NOT TARGET uninstall)
  # Add uninstall target, in linux simply issue xargs rm < install_manifest.txt
  configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/CMake/cmake_uninstall.cmake.in"
      "${CMAKE_CURRENT_BINARY_DIR}/CMake/cmake_uninstall.cmake"
      IMMEDIATE @ONLY)
  add_custom_target(uninstall
      COMMAND ${CMAKE_COMMAND} -P
      ${CMAKE_CURRENT_BINARY_DIR}/CMake/cmake_uninstall.cmake)
endif()
