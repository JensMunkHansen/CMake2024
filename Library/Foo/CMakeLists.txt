include(GenerateExportHeader)

# File: target_public_headers.cmake
macro(target_public_headers TARGET)
  set_target_properties(${TARGET} PROPERTIES PUBLIC_HEADER "${ARGN}")
endmacro()

configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

# sources
set(Foo_SOURCES
  Foo.cxx
)
set(Foo_HEADERS
  Foo.h
)
# public headers
set(Foo_PUBLIC_HEADERS
  Foo.h
  ${CMAKE_CURRENT_BINARY_DIR}/config.h
  ${CMAKE_CURRENT_BINARY_DIR}/foo_export.h
)

add_library(Foo ${Foo_SOURCES} ${Foo_HEADERS} config.h.in)

generate_export_header(Foo)
# state that anybody linking to us needs to include the current source dir
# to find interface headers, while we don't need it.
target_include_directories(Foo
                           INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
			   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                           $<INSTALL_INTERFACE:include>)

# We depend on our binary dir to find export header
target_include_directories(Foo PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR})

# Declare public headers for external build and install			
target_public_headers(Foo "${Foo_PUBLIC_HEADERS}")

# On windows, we append "d" as debug postfix
if (WIN32 AND NOT DEFINED CMAKE_DEBUG_POSTFIX)
  set_target_properties(Foo
    PROPERTIES
    DEBUG_POSTFIX "d")
endif()

# link Foo to compiler flags
target_link_libraries(Foo PUBLIC sps_compiler_flags)

# setup the version numbering
set_property(TARGET Foo PROPERTY VERSION "${Library_VERSION}")
set_property(TARGET Foo PROPERTY SOVERSION "1")

# installs libs
set(installable_libs Foo sps_compiler_flags)

install(TARGETS ${installable_libs}
        EXPORT FooTargets
        LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include/Foo)

