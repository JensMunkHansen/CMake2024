include(ExternalData)

if(NOT SPS_DATA_STORE)
  # Select a default from the following.
  set(SPS_DATA_STORE_DEFAULT "")
  if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/../SPSExternalData")
    # Adjacent directory created by user.
    get_filename_component(SPS_DATA_STORE_DEFAULT
      "${CMAKE_SOURCE_DIR}/../SPSExternalData" ABSOLUTE)
  endif()
endif()

# Provide users with an option to select a local object store,
# starting with the above-selected default.
set(SPS_DATA_STORE "${SPS_DATA_STORE_DEFAULT}" CACHE PATH
  "Local directory holding ExternalData objects in the layout %(algo)/%(hash).")
mark_as_advanced(SPS_DATA_STORE)

# Use a store in the build tree if none is otherwise configured.
if(NOT SPS_DATA_STORE)
  if(ExternalData_OBJECT_STORES)
    set(SPS_DATA_STORE "")
  else()
    set(SPS_DATA_STORE "${CMAKE_BINARY_DIR}/ExternalData/Objects")
    file(MAKE_DIRECTORY "${SPS_DATA_STORE}")
  endif()
endif()

# Tell ExternalData module about selected object stores.
list(APPEND ExternalData_OBJECT_STORES
  # Store selected by configuration above.
  ${SPS_DATA_STORE}

  # Local data store populated by the VTK pre-commit hook - contains link to ~/.ExternalData
  "${CMAKE_SOURCE_DIR}/.ExternalData"
)

set(ExternalData_BINARY_ROOT ${CMAKE_BINARY_DIR}/ExternalData)

set(ExternalData_URL_TEMPLATES "" CACHE STRING
  "Additional URL templates for the ExternalData CMake script to look for testing data.")
mark_as_advanced(ExternalData_URL_TEMPLATES)

set(SPS_FALLBACK_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Testing/LocalData")

if(NOT SPS_FORBID_DOWNLOADS)
  list(APPEND ExternalData_URL_TEMPLATES
    # Data shared from local linux machine
    #"file:///home/jmh/assets/data/%(algo)/%(hash)"
    # Data shared from local machine
    #"file:////DK-DTC-JEHN/Users/jens hansen/assets/data/%(algo)/%(hash)"
    "${SPS_FALLBACK_DATA_DIR}/{name}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Filters/Modeling/Testing/Data/Baseline/{name}"
  )
endif()

# Tell ExternalData commands to transform raw files to content links.
set(ExternalData_LINK_CONTENT SHA512)

# Match series of the form <base>.<ext>, <base>_<n>.<ext> such that <base> may
# end in a (test) number that is not part of any series numbering.
set(ExternalData_SERIES_PARSE "()(\\.[^./]*)$")
set(ExternalData_SERIES_MATCH "(_[0-9]+)?")

if(NOT DEFINED SPS_DATA_EXCLUDE_FROM_ALL)
  if(DEFINED "ENV{SPS_DATA_EXCLUDE_FROM_ALL}")
    set(SPS_DATA_EXCLUDE_FROM_ALL_DEFAULT
      "$ENV{SPS_DATA_EXCLUDE_FROM_ALL}")
  else()
    set(SPS_DATA_EXCLUDE_FROM_ALL_DEFAULT OFF)
  endif()
  set(SPS_DATA_EXCLUDE_FROM_ALL "${SPS_DATA_EXCLUDE_FROM_ALL_DEFAULT}"
    CACHE BOOL "Exclude test data download from default 'all' target."
    )
  mark_as_advanced(SPS_DATA_EXCLUDE_FROM_ALL)
endif()
