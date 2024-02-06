# TODO: Runtime-path not set correctly...

cmake_minimum_required(VERSION 3.15)

project(LibraryUsage
  VERSION 1.0.0
  LANGUAGES CXX)

find_package(Foo REQUIRED)

add_executable(FooUsage main.cxx)
target_link_libraries(FooUsage PRIVATE Foo)

# Consider setting rpath like this and keep all libraries in once place
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# This will stop stripping rpath - but then it is not moveable
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

install(TARGETS FooUsage
  EXPORT FooUsageTargets
  DESTINATION bin
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/FooUsage")

# install the configuration targets
install(EXPORT FooUsageTargets
  FILE FooUsageTargets.cmake
  DESTINATION bin
)

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
