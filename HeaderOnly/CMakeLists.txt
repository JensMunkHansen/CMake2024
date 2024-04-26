cmake_minimum_required(VERSION 3.7)

project(mylib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
#add_compile_options(-Wa -aslh)


# Define the library target
add_library(mylib INTERFACE)
target_include_directories(mylib INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/mylibConfigVersion.cmake"
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

install(TARGETS mylib
    EXPORT mylibTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/mylibConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/mylibConfig.cmake"
    INSTALL_DESTINATION lib/cmake/mylib
)

install(EXPORT mylibTargets DESTINATION lib/cmake/mylib)
install(FILES "${PROJECT_BINARY_DIR}/mylibConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/mylibConfig.cmake"
        DESTINATION lib/cmake/mylib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)


add_executable(mytest test/basic_checks.cxx)
target_link_libraries(mytest mylib)
