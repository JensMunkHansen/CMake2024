cmake_minimum_required(VERSION 3.15..3.22)

# We use SameMajorVersion, consider AnyNewerVersion

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# set the project name and version
project(DeepLibrary
  LANGUAGES CXX
  VERSION 1.0.0)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Same compiler flags everywhere
include(CompilerFlags)

# Libraries
add_subdirectory(Deep)

# Install and deployment. Not needed for in source development
#include(GNUInstallDirs)
include(BuildConfig)

install(EXPORT DeepTargets
#  NAMESPACE ${PROJECT_NAMESPACE}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Deep
  COMPONENT Devel)

include(CMakePackageConfigHelpers)
configure_package_config_file(DeepConfig.cmake.in
  "${PROJECT_BINARY_DIR}/DeepConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Deep"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/DeepConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion)
install(
  FILES
  "${PROJECT_BINARY_DIR}/DeepConfig.cmake"
  "${PROJECT_BINARY_DIR}/DeepConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Deep"
  COMPONENT Devel)

# install the configuration targets
install(EXPORT DeepTargets
  FILE DeepTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Deep
)

include(CMakePackageConfigHelpers)

# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/DeepConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/DeepConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/Deep"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DeepConfigVersion.cmake"
  VERSION "${Library_VERSION_MAJOR}.${Library_VERSION_MINOR}"
  COMPATIBILITY SameMajorVersion
)

# install the configuration files
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/DeepConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/DeepConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Deep
  COMPONENT Devel
  )

# generate the export targets for the build tree
# needs to be after the install(TARGETS ) command
export(EXPORT DeepTargets
  #  NAMESPACE Deep:: # TODO: Figure out how to use namespaces
  FILE "${CMAKE_CURRENT_BINARY_DIR}/DeepTargets.cmake"
)

# Enable writing to registry
set(CMAKE_EXPORT_PACKAGE_REGISTRY 1)
# Export the package for use from the build-tree (this registers the build-tree with a global CMake-registry)
export(PACKAGE Deep)

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

