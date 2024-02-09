# Fron CMake 3.11, we can skip the empty quotes

include(GenerateExportHeader)

add_library(Deep "")

configure_file(include/deep/Config.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/Deep/Config.h" @ONLY)

target_sources(Deep
  PUBLIC
    include/Deep/Deep.h
    # Visual studio hack
    ${CMAKE_CURRENT_BINARY_DIR}/include/Deep/Config.h
  PRIVATE
    src/Deep.cxx)

target_include_directories(Deep
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_features(Deep PUBLIC cxx_std_17)

set_target_properties(Deep PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  POSITION_INDEPENDENT_CODE ON
  INTERFACE_POSITION_INDEPENDENT_CODE ON
  PUBLIC_HEADER include/Deep/Deep.hpp)

generate_export_header(Deep
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/Deep/Deep_export.h
  PREFIX_NAME TS_  
)

#target_link_libraries(Deep PUBLIC ...) # Check IDE
add_library(${PROJECT_NAMESPACE}::Deep ALIAS Deep)

add_subdirectory(tests)

add_subdirectory(python)

add_subdirectory(dotnet)

install(TARGETS Deep
  EXPORT DeepTargets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Deep
)
