# File: FooConfig.cmake
# Location: lib/
#
# This is platform-independent script.
#
# Redirect configuration to the platform-specific script <system>/<cpu>/lib/FooConfig.cmake.
include(${CMAKE_CURRENT_LIST_DIR}/../${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}/lib/FooConfig.cmake)


# Load information for each installed configuration.
file(GLOB _cmake_config_files "${CMAKE_CURRENT_LIST_DIR}/fmt-targets-*.cmake")
foreach(_cmake_config_file IN LISTS _cmake_config_files)
  include("${_cmake_config_file}")
endforeach()
unset(_cmake_config_file)
unset(_cmake_config_files)
