# TODO: Consider if we should make a subdirectory with the same name

include(GenerateExportHeader)

# Dummy test for compiler features
include(CompilerFeatures)
if(HAVE_LOG AND HAVE_EXP)
  message("We have log and exp")
endif()
  
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
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${PROJECT_BINARY_DIR} # for export header
    ${PROJECT_SOURCE_DIR} # Foo/Foo.h
)

# Declare public headers for external build and install			
target_public_headers(Foo "${Foo_PUBLIC_HEADERS}")

# On windows, we append "d" as debug postfix
if (WIN32 AND NOT DEFINED CMAKE_DEBUG_POSTFIX)
  set_target_properties(Foo
    PROPERTIES
    DEBUG_POSTFIX "d")
endif()

# state that SqrtLibrary need PIC when the default is shared libraries
set_target_properties(Foo PROPERTIES
  POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

# link Foo to compiler flags
target_link_libraries(Foo PUBLIC sps_compiler_flags)

# setup the version numbering
set_property(TARGET Foo PROPERTY VERSION "${Library_VERSION}")
set_property(TARGET Foo PROPERTY SOVERSION "1")

# installs libs
set(installable_libs Foo sps_compiler_flags)

install(TARGETS ${installable_libs}
  EXPORT ${PROJECT_NAME}Targets
  DESTINATION lib
  COMPONENT ${PROJECT_NAME}_Devel
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
          COMPONENT ${PROJECT_NAME}_Runtime
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
          COMPONENT ${PROJECT_NAME}_Devel
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
          COMPONENT ${PROJECT_NAME}_Devel
	  NAMELINK_COMPONENT ${PROJECT_NAME}_Devel
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/Foo")

