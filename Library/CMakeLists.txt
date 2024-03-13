cmake_minimum_required(VERSION 3.15..3.22)

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

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# set the project name and version
project(Library2
  LANGUAGES CXX
  VERSION 1.0.0)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_TESTING "Build testing" ON)
# On Windows, this is store in the registry. On other platforms, inside $HOME/.cmake/packages
option(EXPORT_TO_PACKAGE_REGISTRY "Export installation to package registry" OFF)

add_library(build INTERFACE)
add_library(Library2::build ALIAS build)
target_sources(build PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)

# TODO: Avoid using this macro
include(target_public_headers)

include(InstallDirs)

include(TestConfig)
include(CompilerFlags)

add_subdirectory(Foo)

add_subdirectory(FooApp)

if (BUILD_TESTING)
  add_subdirectory(FooTest)
endif()

# Installation and deployment (we could introduce some convenience macros)
install(TARGETS build EXPORT "${PROJECT_NAME}Targets")

# install the configuration targets
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Enable writing to registry
if (EXPORT_TO_PACKAGE_REGISTRY)
  set(CMAKE_EXPORT_PACKAGE_REGISTRY 1)
endif()

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${Library2_VERSION_MAJOR}.${Library2_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

# install the configuration files
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  COMPONENT ${PROJECT_NAME}_Devel #
  # EXCLUDE_FROM_ALL # If enabled, you must specify which component that you want, e.g. Devel
  )

# generate the export targets for the build tree
# needs to be after the install(TARGETS ) command
export(EXPORT ${PROJECT_NAME}Targets
  #  NAMESPACE Foo:: # Not using namespaces
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
)

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
# If CMAKE_EXPORT_PACKAGE_REGISTRY == 0, this does nothing (default) 
export(PACKAGE ${PROJECT_NAME})

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

# setup installer using CPack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Library2_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Library2_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Packaging")

include(CPack)
