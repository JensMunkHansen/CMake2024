# Fron CMake 3.11, we can skip the empty quotes

add_library(Deep "")

configure_file(include/deep/Config.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/deep/Config.h" @ONLY)

target_sources(Deep
  PUBLIC
    include/deep/Deep.h
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
  PUBLIC_HEADER include/foo/Deep.hpp)

#target_link_libraries(Deep PUBLIC ...) # Check IDE
add_library(${PROJECT_NAMESPACE}::Deep ALIAS Deep)

add_subdirectory(tests)

add_subdirectory(python)

add_subdirectory(dotnet)

install(TARGETS Deep
  EXPORT DeepTargets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/deep
)
