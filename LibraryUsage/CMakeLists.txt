# TODO: Runtime-path not set correctly...

cmake_minimum_required(VERSION 3.15)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

project(LibraryUsage
  VERSION 1.0.0
  LANGUAGES CXX)

if (WIN32)
  set(CMAKE_DEBUG_POSTFIX d)
  include(GNUInstallDirs)
else()
  include(BuildConfig) # Not yet deploying DLL's correctly
endif()

find_package(Library2 REQUIRED)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(FooUsage main.cxx)
# TODO: Consider using namespace
target_link_libraries(FooUsage PRIVATE Foo)


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
