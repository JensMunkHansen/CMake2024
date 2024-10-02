# CMakefile for ThreeShape VTK modules


# All policies in range 3.8 - 3.12 is set to NEW.
# Maintenance: We update the version if required
cmake_minimum_required(VERSION 3.8...3.12 FATAL_ERROR)

# Maintenance: Enable, when we support deploying an SDK
# option(TS_INSTALL_SDK "Install SDK components" ON)

include(CMakeDependentOption)

# We need a very short project name without dots, since we
# use it for export declarations, e.g. TS_
project(ts
  LANGUAGES
  CXX)

# Location for custom cmake macros
set(ts_cmake_dir ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH ${ts_cmake_dir})


include(tsVersion)
set(TS_VERSION
    "${TS_MAJOR_VERSION}.${TS_MINOR_VERSION}.${TS_BUILD_VERSION}")
#determine_version("${CMAKE_CURRENT_SOURCE_DIR}" "${GIT_EXECUTABLE}" "TS")
message("Building vtkTS with version: ${TS_VERSION}")


set(ts_VTK_VERSION_MINIMUM 9.3)

find_package(VTK ${ts_VTK_VERSION_MINIMUM})

if(VTK_VERSION VERSION_LESS tsVTK_VERSION_MINIMUM)
  message(FATAL_ERROR "VTK ${tsVTK_VERSION_MINIMUM} or later is required.")
endif()

option(BUILD_SHARED_LIBS "Build shared libraries." OFF)

option(TS_BUILD_TESTING "Build the tests" OFF)

# Wrap Python option (requires that VTK is compiled with python wrappers)
if(VTK_WRAP_PYTHON)
  # Temporarily disable python wrappers!!!
  option(BUILD_PYTHON_WRAPPERS "Build python wrappers" OFF)

  # These are required if we want to create a wheels distribution
  set_property(GLOBAL PROPERTY _ts_python_soabi "${Python3_SOABI}")
  get_property(ts_soabi GLOBAL PROPERTY _ts_python_soabi)
  # TODO: Support release version of Python and verify debugging is working
  cmake_dependent_option(TS_WINDOWS_PYTHON_DEBUGGABLE "Append `_d` to Python module names" OFF
    "WIN32;VTK_WRAP_PYTHON" OFF)
  mark_as_advanced(TS_WINDOWS_PYTHON_DEBUGGABLE)
else()
  unset(BUILD_PYTHON_WRAPPERS CACHE)
endif()

# List of requested and rejected modules controlling what is build
set(ts_requested_modules)
set(ts_rejected_modules)

# Standard install dirs (ADR)
include(GNUInstallDirs)

# Interface target for distribution flags across multiple target
add_library(tsbuild INTERFACE)
add_library(TS::tsbuild ALIAS tsbuild)

# Maintenance: All project wide compiler flags are handled in this section
#              Have impact on the produced binaries and compatiblity to hardware
include(tsCompilerFlags)
include(tsTesting)

option(TS_RELOCATABLE_INSTALL "Do not embed hard-coded paths into the install" ON)
mark_as_advanced(TS_RELOCATABLE_INSTALL)

set(TS_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

# This is standard procedure for hiding symbols
# Maintenance: When we can set this on the interface target [tsbuild], we will do this instead
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Grouping of modules into kits
cmake_dependent_option(TS_ENABLE_KITS "Enable kits compilation" OFF
  # Static builds don't make sense with kits. Ignore the flag if shared
  # libraries aren't being built.
  "TS_BUILD_SHARED_LIBS" OFF)
mark_as_advanced(TS_ENABLE_KITS)


# Set up our directory structure for output libraries and binaries
# (Note: these are the build locations, not the install locations)
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ts_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
endif()

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  if(UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ts_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
  else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ts_BINARY_DIR}${CMAKE_INSTALL_BINDIR}")
  endif()
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ts_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
endif()

# Export name used for export declarations
set(ts_install_export TS)

# Install destination
if (NOT DEFINED ts_cmake_destination)
  set(ts_cmake_destination
    "${CMAKE_INSTALL_LIBDIR}/cmake/ts${ts_version_suffix}")
  set(ts_target_package)
endif()
install(TARGETS tsbuild EXPORT "${ts_install_export}")

option(TS_BUILD_ALL_MODULES "Build all modules by default" OFF)
mark_as_advanced(TS_BUILD_ALL_MODULES)

# Here list what is needed
list(APPEND ts_requested_modules
  TS::CommonCore
)

# Maintenance: This is hardcoded. We should have a default list of modules and the
#              we can enable/disable stuff
if (1)
  set(ts_requested_modules
    TS::CommonCore
  )
endif()

# Option for clearing modules
option(TS_REJECT_ALL_MODULES "Reject all modules" OFF)
if (TS_REJECT_ALL_MODULES)
  set(ts_requested_modules SPS::CommonCore)
endif()

# Remove duplicates
if (ts_requested_modules)
  list(REMOVE_DUPLICATES ts_requested_modules)
endif ()
if (ts_rejected_modules)
  list(REMOVE_DUPLICATES ts_rejected_modules)
endif ()

# Directories to search for modules
set(ts_source_directories
  "${CMAKE_CURRENT_SOURCE_DIR}/Common"
)

# Find all modules described in vtk.module files
vtk_module_find_modules(ts_module_files ${ts_source_directories})

# Find all kits described in vtk.kit files
vtk_module_find_kits(ts_kit_files ${ts_source_directories})

vtk_module_scan(
  MODULE_FILES        ${ts_module_files}
  KIT_FILES           ${ts_kit_files}
  REQUEST_MODULES     ${ts_requested_modules}
  REJECT_MODULES      ${ts_rejected_modules}
  PROVIDES_MODULES    ts_modules
  PROVIDES_KITS       ts_kits
  WANT_BY_DEFAULT     "${TS_BUILD_ALL_MODULES}"
  ENABLE_TESTS        "${TS_BUILD_TESTING}")

if (NOT DEFINED ts_cmake_destination)
  set(ts_cmake_destination
    "${CMAKE_INSTALL_LIBDIR}/cmake/ts${ts_version_suffix}")
endif()

if (VTK_WRAP_PYTHON)
  if (NOT DEFINED TS_PYTHON_SITE_PACKAGES_SUFFIX)
    vtk_module_python_default_destination(TS_PYTHON_SITE_PACKAGES_SUFFIX)
  endif()
endif()

option(TS_VERSIONED_INSTALL "Install artifacts with versioned names." ON)
mark_as_advanced(TS_VERSIONED_INSTALL)

set(ts_version_suffix "")
if (TS_VERSIONED_INSTALL)
  set(ts_version_suffix "-${TS_MAJOR_VERSION}.${TS_MINOR_VERSION}")
endif ()

set(TS_CUSTOM_LIBRARY_SUFFIX "<DEFAULT>"
  CACHE STRING "Custom library file name suffix (defaults to the version number)")
mark_as_advanced(TS_CUSTOM_LIBRARY_SUFFIX)
if (TS_CUSTOM_LIBRARY_SUFFIX STREQUAL "<DEFAULT>")
  if (TS_VERSIONED_INSTALL)
    set(TS_CUSTOM_LIBRARY_SUFFIX "${TS_MAJOR_VERSION}.${TS_MINOR_VERSION}")
  else ()
    set(TS_CUSTOM_LIBRARY_SUFFIX "")
  endif ()
endif ()

vtk_module_build(
  MODULES               ${ts_modules}
  KITS                  ${ts_kits}
  INSTALL_EXPORT        "${ts_install_export}"
  ARCHIVE_DESTINATION   "lib"
  HEADERS_DESTINATION   "${CMAKE_INSTALL_INCLUDEDIR}/ts${ts_version_suffix}"
  CMAKE_DESTINATION     "${ts_cmake_destination}"
  LICENSE_DESTINATION   "${CMAKE_INSTALL_LIBDIR}/ts"
  LIBRARY_NAME_SUFFIX   "${TS_CUSTOM_LIBRARY_SUFFIX}"
  HIERARCHY_DESTINATION "${CMAKE_INSTALL_LIBDIR}/ts${ts_version_suffix}/hierarchy/${CMAKE_PROJECT_NAME}"
  VERSION               "${TS_VERSION}"
  SOVERSION             "1" # If the library is small and should work as a remote module to VTK
  TEST_DATA_TARGET      TsData
  INSTALL_HEADERS       "${TS_INSTALL_SDK}"
#  USE_FILE_SETS         ON
  BUILD_WITH_KITS       "${TS_ENABLE_KITS}"
  USE_EXTERNAL          "${TS_USE_EXTERNAL}"  
  TEST_INPUT_DATA_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/Testing"
  TEST_OUTPUT_DATA_DIRECTORY  "${CMAKE_CURRENT_BINARY_DIR}/ExternalData/Testing")

if(BUILD_PYTHON_WRAPPERS)
  find_package(PythonInterp ${VTK_PYTHON_VERSION} QUIET)

  vtk_module_wrap_python(
    MODULES         ${ts_modules}
    INSTALL_EXPORT  TSPython
    PYTHON_PACKAGE  "tsmodules"
    LIBRARY_DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    MODULE_DESTINATION  "${TS_PYTHON_SITE_PACKAGES_SUFFIX}"
    CMAKE_DESTINATION   "${ts_cmake_destination}"
    INSTALL_HEADERS     "${TS_INSTALL_SDK}"
    SOABI               "${ts_soabi}" # TODO: Needed for a future wheels build
    USE_DEBUG_SUFFIX    "${TS_WINDOWS_PYTHON_DEBUGGABLE}"
    UTILITY_TARGET      "TS::tsbuild"
    WRAPPED_MODULES     ts_python_wrapped_modules
    BUILD_STATIC        OFF) # We do not support static python wrappers

  # Display a list of the wrapped modules
  message("Wrapped modules include:")
  foreach(ts_python_wrapped_module ${ts_python_wrapped_modules})
    message("  ${ts_python_wrapped_module}")
  endforeach()

  add_subdirectory(Wrapping/Python)

  export(
    EXPORT    TSPython
    NAMESPACE TS::
    FILE      "${CMAKE_BINARY_DIR}/${ts_cmake_destination}/TSPython-targets.cmake")
  install(
    EXPORT      TSPython
    NAMESPACE   TS::
    FILE        TSPython-targets.cmake
    DESTINATION "${ts_cmake_destination}"
    COMPONENT   "development")

endif()

# Used for potential new way of installation
if (TS_INSTALL_SDK)
  set(ts_cmake_build_dir
    "${CMAKE_CURRENT_BINARY_DIR}/${ts_cmake_destination}")
  include(tsInstallCMakePackage)
endif()

if (TS_BUILD_TESTING)
  # Exclude the project TsData project, which downloads the data
  if(TS_DATA_EXCLUDE_FROM_ALL)
    set_property(TARGET TsData PROPERTY EXCLUDE_FROM_ALL 1)
    if(TS_BUILD_TESTING AND NOT TS_DATA_EXCLUDE_FROM_ALL_NO_WARNING)
      message(WARNING "TS_DATA_EXCLUDE_FROM_ALL is ON so test data "
        "(needed because TS_BUILD_TESTING is ON) may not be available "
        "without manually building the 'TSData' target.")
    endif()
  endif()
  # TODO: Decide if we want to use CMake's ExternalData functionality
  #ExternalData_Add_Target(TsData)
  enable_testing()
endif()

# Build examples. TODO: Include these like they do in VTK
if (TS_BUILD_EXAMPLES)
  message("Build examples enabled")
  add_subdirectory(Examples)
endif()

if (NOT TARGET UNINSTALL)
  add_custom_target(UNINSTALL
    COMMAND
      "${CMAKE_COMMAND}"
        "-DCMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}"
        -P "${CMAKE_CURRENT_LIST_DIR}/CMake/tsUninstall.cmake"
    USES_TERMINAL
    COMMENT "Uninstalling TS")
endif ()
