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

include(target_public_headers)
if (WIN32)
  set(CMAKE_DEBUG_POSTFIX d)
  include(GNUInstallDirs)
else()
  include(BuildConfig) # Not yet deploying DLL's correctly
endif()

include(TestConfig)
include(CompilerFlags)

add_subdirectory(Foo)

add_subdirectory(FooApp)

if (BUILD_TESTING)
  add_subdirectory(FooTest)
endif()

# install the configuration targets
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
)

# Enable writing to registry
set(CMAKE_EXPORT_PACKAGE_REGISTRY 1)

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
  VERSION "${Library_VERSION_MAJOR}.${Library_VERSION_MINOR}"
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
  #  NAMESPACE Foo:: # TODO: Figure out how to use namespaces
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
)

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
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
set(CPACK_PACKAGE_VERSION_MAJOR "${Library_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Library_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Packaging")

include(CPack)
