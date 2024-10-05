# CMakefile for custom VTK modules


# All policies in range 3.8 - 3.12 is set to NEW.
# Maintenance: We update the version if required
cmake_minimum_required(VERSION 3.8...3.12 FATAL_ERROR)

# Maintenance: Enable, when we support deploying an SDK
# option(SPS_INSTALL_SDK "Install SDK components" ON)

include(CMakeDependentOption)

# We need a very short project name without dots, since we
# use it for export declarations, e.g. SPS_
project(sps
  LANGUAGES
  CXX)

# Location for custom cmake macros
set(sps_cmake_dir ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH ${sps_cmake_dir})


include(spsVersion)
set(SPS_VERSION
    "${SPS_MAJOR_VERSION}.${SPS_MINOR_VERSION}.${SPS_BUILD_VERSION}")
message("Building vtkSPS with version: ${SPS_VERSION}")

set(sps_VTK_VERSION_MINIMUM 9.1)

find_package(VTK ${sps_VTK_VERSION_MINIMUM})

if(VTK_VERSION VERSION_LESS spsVTK_VERSION_MINIMUM)
  message(FATAL_ERROR "VTK ${spsVTK_VERSION_MINIMUM} or later is required.")
endif()

option(BUILD_SHARED_LIBS "Build shared libraries." OFF)

option(SPS_BUILD_TESTING "Build the tessps" OFF)

# Wrap Python option (requires that VTK is compiled with python wrappers)
if(VTK_WRAP_PYTHON)
  option(BUILD_PYTHON_WRAPPERS "Build python wrappers" ON)

  # These are required if we want to create a wheels distribution
  set_property(GLOBAL PROPERTY _sps_python_soabi "${Python3_SOABI}")
  get_property(sps_soabi GLOBAL PROPERTY _sps_python_soabi)

  # TODO: Support release version of Python and verify debugging is working
  cmake_dependent_option(SPS_WINDOWS_PYTHON_DEBUGGABLE "Append `_d` to Python module names" OFF
    "WIN32;VTK_WRAP_PYTHON" OFF)
  mark_as_advanced(SPS_WINDOWS_PYTHON_DEBUGGABLE)
else()
  unset(BUILD_PYTHON_WRAPPERS CACHE)
endif()

# List of requested and rejected modules controlling what is build
set(sps_requested_modules)
set(sps_rejected_modules)

# Standard install dirs (ADR)
include(GNUInstallDirs)

# Interface target for distribution flags across multiple target
add_library(spsbuild INTERFACE)
add_library(SPS::spsbuild ALIAS spsbuild)

# Maintenance: All project wide compiler flags are handled in this section
#              Have impact on the produced binaries and compatiblity to hardware
include(spsCompilerFlags)
include(spsTesting)
include(spsUtilities)

option(SPS_RELOCATABLE_INSTALL "Do not embed hard-coded paths into the install" ON)
mark_as_advanced(SPS_RELOCATABLE_INSTALL)

set(SPS_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

# This is standard procedure for hiding symbols
# Maintenance: When we can set this on the interface target [spsbuild], we will do this instead
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Grouping of modules into kisps
cmake_dependent_option(SPS_ENABLE_KITS "Enable kits compilation" OFF
  # Static builds don't make sense with kits. Ignore the flag if shared
  # libraries aren't being built.
  "SPS_BUILD_SHARED_LIBS" OFF)
mark_as_advanced(SPS_ENABLE_KITS)


# Set up our directory structure for output libraries and binaries
# (Note: these are the build locations, not the install locations)
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${sps_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
endif()

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  if(UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${sps_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
  else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${sps_BINARY_DIR}${CMAKE_INSTALL_BINDIR}")
  endif()
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${sps_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
endif()

# Export name used for export declarations
set(sps_install_export SPS)

# Install destination
if (NOT DEFINED sps_cmake_destination)
  set(sps_cmake_destination
    "${CMAKE_INSTALL_LIBDIR}/cmake/sps${sps_version_suffix}")
  set(sps_target_package)
endif()
install(TARGETS spsbuild EXPORT "${sps_install_export}")

option(SPS_BUILD_ALL_MODULES "Build all modules by default" OFF)
mark_as_advanced(SPS_BUILD_ALL_MODULES)

# Here list what is needed
list(APPEND sps_requested_modules
  SPS::CommonCore
  SPS::CommonDataModel
  SPS::FiltersModeling
  SPS::IOGeneral
)

# Option for clearing modules
option(SPS_REJECT_ALL_MODULES "Reject all modules" OFF)
if (SPS_REJECT_ALL_MODULES)
  set(sps_requested_modules SPS::CommonCore)
endif()

# Remove duplicates
if (sps_requested_modules)
  list(REMOVE_DUPLICATES sps_requested_modules)
endif ()
if (sps_rejected_modules)
  list(REMOVE_DUPLICATES sps_rejected_modules)
endif ()

# Directories to search for modules
set(sps_source_directories
  "${CMAKE_CURRENT_SOURCE_DIR}/Common"
  "${CMAKE_CURRENT_SOURCE_DIR}/Filters"
  "${CMAKE_CURRENT_SOURCE_DIR}/IO"
)

# Find all modules described in vtk.module files
vtk_module_find_modules(sps_module_files ${sps_source_directories})

# Find all kits described in vtk.kit files
vtk_module_find_kits(sps_kit_files ${sps_source_directories})

vtk_module_scan(
  MODULE_FILES        ${sps_module_files}
  KIT_FILES           ${sps_kit_files}
  REQUEST_MODULES     ${sps_requested_modules}
  REJECT_MODULES      ${sps_rejected_modules}
  PROVIDES_MODULES    sps_modules
  PROVIDES_KITS       sps_kits
  WANT_BY_DEFAULT     "${SPS_BUILD_ALL_MODULES}"
  ENABLE_TESTS        "${SPS_BUILD_TESTING}")

if (NOT DEFINED sps_cmake_destination)
  set(sps_cmake_destination
    "${CMAKE_INSTALL_LIBDIR}/cmake/sps${sps_version_suffix}")
endif()

if (VTK_WRAP_PYTHON)
  if (NOT DEFINED SPS_PYTHON_SITE_PACKAGES_SUFFIX)
    vtk_module_python_default_destination(SPS_PYTHON_SITE_PACKAGES_SUFFIX)
  endif()
endif()

option(SPS_VERSIONED_INSTALL "Install artifacts with versioned names." ON)
mark_as_advanced(SPS_VERSIONED_INSTALL)

set(sps_version_suffix "")
if (SPS_VERSIONED_INSTALL)
  set(sps_version_suffix "-${SPS_MAJOR_VERSION}.${SPS_MINOR_VERSION}")
endif ()

set(SPS_CUSTOM_LIBRARY_SUFFIX "<DEFAULT>"
  CACHE STRING "Custom library file name suffix (defaults to the version number)")
mark_as_advanced(SPS_CUSTOM_LIBRARY_SUFFIX)
if (SPS_CUSTOM_LIBRARY_SUFFIX STREQUAL "<DEFAULT>")
  if (SPS_VERSIONED_INSTALL)
    set(SPS_CUSTOM_LIBRARY_SUFFIX "${SPS_MAJOR_VERSION}.${SPS_MINOR_VERSION}")
  else ()
    set(SPS_CUSTOM_LIBRARY_SUFFIX "")
  endif ()
endif ()

vtk_module_build(
  MODULES               ${sps_modules}
  KITS                  ${sps_kits}
  INSTALL_EXPORT        "${sps_install_export}"
  ARCHIVE_DESTINATION   "lib"
  HEADERS_DESTINATION   "${CMAKE_INSTALL_INCLUDEDIR}/sps${sps_version_suffix}"
  CMAKE_DESTINATION     "${sps_cmake_destination}"
  LICENSE_DESTINATION   "${CMAKE_INSTALL_LIBDIR}/sps"
  LIBRARY_NAME_SUFFIX   "${SPS_CUSTOM_LIBRARY_SUFFIX}"
  HIERARCHY_DESTINATION "${CMAKE_INSTALL_LIBDIR}/sps${sps_version_suffix}/hierarchy/${CMAKE_PROJECT_NAME}"
  VERSION               "${SPS_VERSION}"
  SOVERSION             "1" # If the library is small and should work as a remote module to VTK
  TEST_DATA_TARGET      SpsData
  INSTALL_HEADERS       "${SPS_INSTALL_SDK}"
  BUILD_WITH_KITS       "${SPS_ENABLE_KITS}"
  USE_EXTERNAL          "${SPS_USE_EXTERNAL}"  
  TEST_INPUT_DATA_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/Testing"
  TEST_OUTPUT_DATA_DIRECTORY  "${CMAKE_CURRENT_BINARY_DIR}/ExternalData/Testing")

  
if(BUILD_PYTHON_WRAPPERS)
  find_package(Python3
    COMPONENTS
    Interpreter
    Development REQUIRED)

  if(NOT VTK_PYTHON_VERSION VERSION_EQUAL Python3_VERSION_MAJOR)
    message(FATAL_ERROR "Python versions must agree")
  endif()
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/spspython.py.in ${CMAKE_CURRENT_SOURCE_DIR}/spspython.py @ONLY)

  vtk_module_wrap_python(
    MODULES             ${sps_modules}
    INSTALL_EXPORT      SPSPython
    PYTHON_PACKAGE      "spsmodules"
    LIBRARY_DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    MODULE_DESTINATION  "${SPS_PYTHON_SITE_PACKAGES_SUFFIX}"
    CMAKE_DESTINATION   "${sps_cmake_destination}"
    INSTALL_HEADERS     "${SPS_INSTALL_SDK}"
    SOABI               "${sps_soabi}" # TODO: Needed for a future wheels build
    USE_DEBUG_SUFFIX    "${SPS_WINDOWS_PYTHON_DEBUGGABLE}"
    UTILITY_TARGET      "SPS::spsbuild"
    WRAPPED_MODULES     sps_python_wrapped_modules
    BUILD_STATIC        OFF) # We do not support static python wrappers

  # Display a list of the wrapped modules
  message("Wrapped modules include:")
  foreach(sps_python_wrapped_module ${sps_python_wrapped_modules})
    message("  ${sps_python_wrapped_module}")
  endforeach()

  add_subdirectory(Wrapping/Python)

  export(
    EXPORT    SPSPython
    NAMESPACE SPS::
    FILE      "${CMAKE_BINARY_DIR}/${sps_cmake_destination}/SPSPython-targets.cmake")
  install(
    EXPORT      SPSPython
    NAMESPACE   SPS::
    FILE        SPSPython-targets.cmake
    DESTINATION "${sps_cmake_destination}"
    COMPONENT   "development")

endif()

# Used for potential new way of installation
if (SPS_INSTALL_SDK)
  set(sps_cmake_build_dir
    "${CMAKE_CURRENT_BINARY_DIR}/${sps_cmake_destination}")
  include(spsInstallCMakePackage)
endif()

if (SPS_BUILD_TESTING)
  # Exclude the project SpsData project, which downloads the data
  if(SPS_DATA_EXCLUDE_FROM_ALL)
    set_property(TARGET SpsData PROPERTY EXCLUDE_FROM_ALL 1)
    if(SPS_BUILD_TESTING AND NOT SPS_DATA_EXCLUDE_FROM_ALL_NO_WARNING)
      message(WARNING "SPS_DATA_EXCLUDE_FROM_ALL is ON so test data "
        "(needed because SPS_BUILD_TESTING is ON) may not be available "
        "without manually building the 'SPSData' target.")
    endif()
  endif()
  # TODO: Decide if we want to use CMake's ExternalData functionality
  #ExternalData_Add_Target(TsData)
  enable_testing()
endif()


# Build examples. TODO: Include these like they do in VTK
if (SPS_BUILD_EXAMPLES)
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
