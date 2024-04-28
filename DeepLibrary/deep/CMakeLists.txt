# Fron CMake 3.11, we can skip the empty quotes
include(GenerateExportHeader)

add_library(Deep "")

configure_file(include/deep/Config.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/deep/Config.h" @ONLY)

target_sources(Deep
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/deep/Deep.h>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/deep/Deep.h>
  PRIVATE
    src/Deep.cxx)

target_include_directories(Deep
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>) # Experiment (WRONG)

target_compile_features(Deep PUBLIC cxx_std_17)

set_target_properties(Deep PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  POSITION_INDEPENDENT_CODE ON
  INTERFACE_POSITION_INDEPENDENT_CODE ON
  PUBLIC_HEADER include/deep/Deep.h)

#target_link_libraries(Deep PUBLIC ...) # Check IDE
add_library(${PROJECT_NAMESPACE}::Deep ALIAS Deep)

generate_export_header(Deep
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/deep/Deep_export.h
  PREFIX_NAME TS_  
)

add_subdirectory(tests)

add_subdirectory(python)

add_subdirectory(dotnet)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/deep/Deep_export.h
DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/deep)

install(TARGETS Deep
  EXPORT DeepTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT Deep_Development
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
          COMPONENT Deep_Runtime
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
          COMPONENT Deep_Develment
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
          COMPONENT Deep_Develment
  NAMELINK_COMPONENT Deep_Devel
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/deep")
