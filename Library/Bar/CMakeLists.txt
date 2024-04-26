# Special target for compiler flags (global)
add_library(algorithms INTERFACE)
add_library(Bar::algorithms ALIAS algorithms)
# setup that we need C++14 support
target_compile_features(algorithms  INTERFACE cxx_std_14)

# Our header-only library
add_library(Bar INTERFACE)

# Inherit the flags
target_link_libraries(Bar INTERFACE algorithms)

# Before the new FILE_SET notation
target_include_directories(Bar INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Bar/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/BarConfigVersion.cmake"
  VERSION "${Library2_VERSION_MAJOR}.${Library2_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion ARCH_INDEPENDENT
)

install(TARGETS Bar algorithms
    EXPORT BarTargets 
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT Bar_Runtime
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT Bar_Development
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT Bar_Runtime
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" COMPONENT Bar_Development
    BUNDLE DESTINATION bin COMPONENT Bar_Runtime
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/BarConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/BarConfig.cmake"
    INSTALL_DESTINATION
      ${CMAKE_INSTALL_LIBDIR}/cmake/Bar
)

install(EXPORT BarTargets DESTINATION lib/cmake/Bar)
install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/BarConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/BarConfigVersion.cmake"
  DESTINATION 
    ${CMAKE_INSTALL_LIBDIR}/cmake/Bar
)
# Before CMake 3.23, we make a manual install for the headers  
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/Bar DESTINATION include)  

# Must be after the install commands
if (0)
export(EXPORT BarTargets
  #  NAMESPACE Foo:: # Not using namespaces
  FILE "${CMAKE_CURRENT_BINARY_DIR}/BarTargets.cmake"
)
endif()

add_executable(BarTest test/basic_checks.cxx)
target_link_libraries(BarTest PUBLIC Bar)

  

  
