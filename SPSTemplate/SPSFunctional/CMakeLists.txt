cmake_minimum_required(VERSION 3.23)

project(SPS
  VERSION 0.1
  LANGUAGES CXX)

# Defines
#  CMAKE_INSTALL_LIBDIR
#  CMAKE_INSTALL_INCLUDEDIR
#  CMAKE_INSTALL_BINDIR
include(GNUInstallDirs)
message("CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR}")
message("CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}")
message("CMAKE_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}")

# On Windows, this is store in the registry. On other platforms, inside $HOME/.cmake/packages
option(EXPORT_TO_PACKAGE_REGISTRY "Export installation to package registry" OFF)

# Enable writing to registry
if (EXPORT_TO_PACKAGE_REGISTRY)
  set(CMAKE_EXPORT_PACKAGE_REGISTRY 1)
endif()

# Build interface
add_library(build INTERFACE)
# These flags are automatically transferred (when linking)
target_compile_features(build INTERFACE cxx_std_17)
add_library(SPS::build ALIAS build)

# Create a new target (header-only)
set(TARGET_NAME SPSFunctional)
add_library(${TARGET_NAME} INTERFACE)
target_sources(${TARGET_NAME}
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/sps/functional.hpp
  PRIVATE
    # Private headers
)

# Include dirs for build tree and install tree
target_include_directories(${TARGET_NAME} INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Enfore flags from build interface
target_link_libraries(${TARGET_NAME} INTERFACE build)

# For both build and install tree. Needed for other libraries to use
# find_package(SPSFunction)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}ConfigVersion.cmake"
  VERSION ${SPS_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Define your exports: If we had binaries they will get exported. Other
# targets in the solution can use them
install(TARGETS ${TARGET_NAME} build # Needed
    EXPORT ${TARGET_NAME}Targets     # Needed
    LIBRARY
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT Runtime
    ARCHIVE
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT Development
    RUNTIME
      DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT Runtime
    FILE_SET public_headers # Only this for header-only, CMake 3.23+
      COMPONENT Development # Only this for header-only
    FRAMEWORK # MacOS (.so and lib)
       COMPONENT Runtime
    BUNDLE # MacOS (exe)
       COMPONENT Runtime
     PRIVATE_HEADER # For private headers (why!!!)
       COMPONENT Development
     RESOURCE
       COMPONENT Development # Windows resources
#     CXX_MODULES_BMI # Binary module interfaces for C++20 (modules), requires CMake 3.28
#       COMPONENT Development
)


# Both build and install tree
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}Config.cmake.in"      # Input
    "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}Config.cmake"         # Build tree
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME} # Install tree
)

# For the install tree (can be skipped completely)
install(
  EXPORT ${TARGET_NAME}Targets
  NAMESPACE SPS::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}) # Install
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}ConfigVersion.cmake" # Already created
    "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}Config.cmake"        # Already created
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME})                   # Install tree

# Generate export targets for the build/install tree
export(EXPORT ${TARGET_NAME}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}Targets.cmake"
  NAMESPACE SPS::
)

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
# If CMAKE_EXPORT_PACKAGE_REGISTRY == 0, this does nothing (default) 
export(PACKAGE ${TARGET_NAME})

# Just test targets (not included for build/install tree)
add_executable(SampleTest Test/SampleTest.cxx)
target_link_libraries(SampleTest PUBLIC ${TARGET_NAME})
  
