include(GenerateExportHeader)

# Fron CMake 3.11, we can skip the empty quotes
add_library(Deep "")

# Config file containing version
configure_file(include/Deep/Config.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/Deep/Config.h" @ONLY)

set(PUBLIC_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/include/Deep/Deep.h
  # Add public headers here
)

target_sources(Deep
  PUBLIC
    $<BUILD_INTERFACE:${PUBLIC_HEADERS}>
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/include/Deep/Config.h
    # Add private headers here
    src/Deep.cxx
    # Add sources here
)

target_include_directories(Deep
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include> # For auto-generated export header
    $<INSTALL_INTERFACE:include>)

set_target_properties(Deep PROPERTIES PUBLIC_HEADER include/Deep/Deep.h)
  
target_compile_features(Deep PUBLIC cxx_std_17)

set_target_properties(Deep PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  POSITION_INDEPENDENT_CODE ON
  INTERFACE_POSITION_INDEPENDENT_CODE ON
  PUBLIC_HEADERS ${PUBLIC_HEADERS})

# TODO: Create macro
generate_export_header(Deep
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/Deep/Deep_export.h
  PREFIX_NAME TS_  
)

#target_link_libraries(Deep PUBLIC ...) # Check IDE
#add_library(${PROJECT_NAMESPACE}::Deep ALIAS Deep)

add_subdirectory(tests)

add_subdirectory(python)

add_subdirectory(dotnet)

# Installation stuff

install(TARGETS Deep
  EXPORT DeepTargets
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Deep"
)
