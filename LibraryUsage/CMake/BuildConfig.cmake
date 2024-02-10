get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

set(CMAKE_DEBUG_POSTFIX d)

if(isMultiConfig)
  if(NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING
    "Choose the type of builds, options are: Debug Release RelWithDebInfo MinSizeRel. (default: Release;Debug)"
    FORCE)
  endif()
  message(STATUS "Configuration types: ${CMAKE_CONFIGURATION_TYPES}")
else()
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
    "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel. (default: Release)"
    FORCE)
  endif()
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()

include(GNUInstallDirs)
if (APPLE)
  set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
endif()

if(UNIX)
  option(BUILD_SHARED_LIBS "Build shared libraries (.so or .dyld)." ON)
  message("Installing RPATH")
  # Makes sense since build and install tree are the same
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE) # TESTME
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}:$ORIGIN")

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  # for multi-config build system (e.g. Xcode, Ninja Multi-Config)
  foreach(OutputConfig IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${OutputConfig} OUTPUTCONFIG)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_BINDIR})
  endforeach()

  # set_property(TARGET my_lib
  #  PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/$<CONFIG>/bin)
  
else()
  # Currently Only support static build for windows
  # option(BUILD_SHARED_LIBS "Build shared libraries (.dll)." OFF)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  # for multi-config builds (e.g. msvc)
  foreach(OutputConfig IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${OutputConfig} OUTPUTCONFIG)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_BINDIR})
  endforeach()
endif()
#if(BUILD_SHARED_LIBS AND MSVC)
#  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#endif()
message(STATUS "Build shared libs: ${BUILD_SHARED_LIBS}")
