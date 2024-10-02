# NOTE: We do not support static Python wrappers like VTK.
#       Static wrappers means linking libraries directly into
#       the python executable.

# This file is copied and adapted from VTK/Wrapping/Python/CMakeLists.txt
# and there is a lot of rendundant material.

set(_spsmodules_all)
set(_sps_python_imports)

foreach (_sps_python_module IN LISTS sps_python_wrapped_modules)
  get_property(_sps_python_library_name
    TARGET    "${_sps_python_module}"
    PROPERTY  "INTERFACE_vtk_module_library_name")
  string(APPEND _spsmodules_all
    "    \'${_sps_python_library_name}\',\n")
  string(APPEND _sps_python_imports
    "from .${_sps_python_library_name} import *\n")
endforeach ()

set(_sps_python_files)
foreach (_sps_module IN LISTS sps_modules)
  _vtk_module_get_module_property("${_sps_module}"
    PROPERTY "python_modules"
    VARIABLE _sps_module_python_files)
  list(APPEND _sps_python_files
    ${_sps_module_python_files})
endforeach()

# Utility function for dumping variables
function(dump_cmake_variables)
  get_cmake_property(_variableNames VARIABLES)
  list (SORT _variableNames)
  foreach (_variableName ${_variableNames})
    if (ARGV0)
      unset(MATCHED)
      string(REGEX MATCH ${ARGV0} MATCHED ${_variableName})
      if (NOT MATCHED)
        continue()
      endif()
    endif()
    message(STATUS "${_variableName}=${${_variableName}}")
  endforeach()
endfunction()

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/spsmodules/all.py.in"
  "${CMAKE_BINARY_DIR}/${SPS_PYTHON_SITE_PACKAGES_SUFFIX}/spsmodules/all.py"
  @ONLY)
list(APPEND _sps_python_files
  "${CMAKE_BINARY_DIR}/${SPS_PYTHON_SITE_PACKAGES_SUFFIX}/spsmodules/all.py")

if (BUILD_SHARED_LIBS)
  install(
    FILES       "${CMAKE_BINARY_DIR}/${SPS_PYTHON_SITE_PACKAGES_SUFFIX}/spsmodules/all.py"
    DESTINATION "${SPS_PYTHON_SITE_PACKAGES_SUFFIX}/spsmodules"
    COMPONENT   "python")
endif ()

# Python files to add
set(python_files
  sps.py
  spsmodules/__init__.py.in
  spsmodules/util/scene_utils.py
)

foreach (python_file IN LISTS python_files)
  # add submodules that don't begin with "_" to _spsmodules_all
  if (python_file MATCHES "^spsmodules\/([A-Za-z][A-Za-z0-9_]*)(\/__init__)?[.]py")
    string(APPEND _spsmodules_all "    \'${CMAKE_MATCH_1}\',\n")
  endif ()
endforeach ()

# TODO: On windows, the wrappers only work in Release mode. The only simple solution that
#       I have come up with is to disable multiple configurations and set
#       CMAKE_BUILD_TYPE=Release. For now, we only support wrappers in Release.....

set(SPS_PYTHON_CONFIGURATION_DEBUG "Debug" CACHE STRING "")
#set(SPS_PYTHON_CONFIGURATION "Debug")
set(SPS_PYTHON_CONFIGURATION_RELEASE "Release" CACHE STRING "")

set(python_copied_modules)
foreach (python_file IN LISTS python_files)
  set(output_python_file
    "${CMAKE_BINARY_DIR}/${SPS_PYTHON_SITE_PACKAGES_SUFFIX}/${python_file}")
  if (python_file MATCHES "\\.in$")
    string(REPLACE ".in" "" output_python_file "${output_python_file}")
    configure_file(
      "${python_file}"
      "${output_python_file}"
      @ONLY)
  else ()
    add_custom_command(
      OUTPUT  "${output_python_file}"
      DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${python_file}"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
              "${CMAKE_CURRENT_SOURCE_DIR}/${python_file}"
              "${output_python_file}"
      COMMENT "Copying ${python_file} to the binary directory")
  endif ()
  if (BUILD_SHARED_LIBS)
    get_filename_component(python_file_directory "${python_file}" DIRECTORY)
    install(
      FILES       "${output_python_file}"
      DESTINATION "${SPS_PYTHON_SITE_PACKAGES_SUFFIX}/${python_file_directory}"
      COMPONENT   "python")
  endif ()
  list(APPEND python_copied_modules
    "${output_python_file}")
endforeach ()

set(sps_build_paths_module
  "${CMAKE_BINARY_DIR}/${SPS_PYTHON_SITE_PACKAGES_SUFFIX}/spsmodules/_build_paths.py")

# Figure out the relevant DLL paths to add on Windows
if (WIN32 AND SPS_DLL_PATHS)
  string(REPLACE ";" "',\n    '" sps_dll_paths_python "${SPS_DLL_PATHS}")
  file(WRITE "${sps_build_paths_module}"
    "paths = [\n    '${sps_dll_paths_python}',\n]\n")
  # Add the file to the zip only if required in the install tree.
  if (NOT SPS_RELOCATABLE_INSTALL AND NOT SPS_UNIFIED_INSTALL_TREE)
    list(APPEND _sps_python_files
      "${sps_build_paths_module}")
  endif ()
elseif (EXISTS "${sps_build_paths_module}")
  file(REMOVE "${sps_build_paths_module}")
endif ()

list(APPEND _sps_python_files
  ${python_copied_modules})

set(_sps_python_zip)

# TODO: Populate if we decide to support STATIC wrappers (we don't)
add_custom_target(sps_python_copy ALL
  DEPENDS
    ${python_copied_modules}
    ${_sps_python_zip})

# TODO: Nice to have. Create proper setup to allow Python tests to locate spsmodules just built.
# At the moment, Python tests cannot execute as a part of the CTest setup.
#if (SPS_BUILD_TESTING)
#  add_subdirectory(Testing)
#endif ()
