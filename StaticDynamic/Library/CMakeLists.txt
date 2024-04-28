cmake_minimum_required(VERSION 3.23...3.26)

project(StackFunction
  LANGUAGES CXX
  VERSION 0.9.0)

# Here we use Catch2 (statically) from the artifactory

add_library(build INTERFACE)
add_library(StackFunction::build ALIAS build)
target_compile_features(build INTERFACE cxx_std_17)

add_library(${PROJECT_NAME} INTERFACE)
# Propagate compiler flags to target
target_link_libraries(${PROJECT_NAME} INTERFACE build)

target_include_directories(${PROJECT_NAME} INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

# Note build target is exported
install(TARGETS ${PROJECT_NAME} build
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(EXPORT ${PROJECT_NAME}Targets DESTINATION lib/cmake/${PROJECT_NAME})
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              DESTINATION lib/cmake/${PROJECT_NAME})

# From CMake 3.23, you can use FILE_SET	
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

# This searches artifactory (due to CMAKE_PREFIX_PATH)
find_package(Catch2)
if (NOT Catch2_FOUND)
  set(BUILD_TESTING OFF)
  message(WARNING "Tests disabled")
  return()
endif()

enable_testing()

set(TEST_NAME mytest)
add_executable(mytest test/TestStackFunction.cxx)
target_link_libraries(${TEST_NAME} PUBLIC ${PROJECT_NAME})
target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain)
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

