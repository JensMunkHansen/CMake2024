cmake_minimum_required(VERSION 3.23)

project(mylib23 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Define the library target
add_library(mylib23 INTERFACE)
target_sources(mylib23
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/sps/functional.hpp)
  
target_include_directories(mylib23 INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/mylib23ConfigVersion.cmake"
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

install(TARGETS mylib23
    EXPORT mylib23Targets
    LIBRARY
      DESTINATION lib
      COMPONENT Runtime
    ARCHIVE
      DESTINATION lib
      COMPONENT Development
    RUNTIME
      DESTINATION bin
      COMPONENT Runtime
    FILE_SET public_headers
      COMPONENT Development
    BUNDLE
      DESTINATION bin
      COMPONENT Runtime
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/mylib23Config.cmake.in"
    "${PROJECT_BINARY_DIR}/mylib23Config.cmake"
    INSTALL_DESTINATION lib/cmake/mylib
)

install(EXPORT mylib23Targets DESTINATION lib/cmake/mylib)
install(FILES "${PROJECT_BINARY_DIR}/mylib23ConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/mylib23Config.cmake"
        DESTINATION lib/cmake/mylib23)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)


add_executable(mytest test/basic_checks.cxx)
target_link_libraries(mytest mylib23)
