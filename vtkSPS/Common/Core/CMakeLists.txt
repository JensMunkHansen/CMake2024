include(CMakeDependentOption)

# Option to mangle SPS symbols
set(SPS_ABI_NAMESPACE_NAME
  "<DEFAULT>"
  CACHE STRING "Inline namespace name for mangling SPS symbols.")
mark_as_advanced(SPS_ABI_NAMESPACE_NAME)

if (SPS_ABI_NAMESPACE_NAME STREQUAL "<DEFAULT>")
  # The default is to not have an ABI namespace.
  # This is consistent with the existing practice.
  set(SPS_ABI_NAMESPACE_NAME "")
endif ()
# We use vtkModuleTesting.cmake (TODO: Use our own variable _sps_abi_namespace_name for inline namespace)
set_property(GLOBAL PROPERTY _vtk_abi_namespace_name "${SPS_ABI_NAMESPACE_NAME}")
if (SPS_ABI_NAMESPACE_NAME STREQUAL "")
  set(SPS_ABI_NAMESPACE_BEGIN "")
  set(SPS_ABI_NAMESPACE_END "")
else ()
  message(STATUS "SPS ABI namespace: ${SPS_ABI_NAMESPACE_NAME}")
  set(SPS_ABI_NAMESPACE_BEGIN "inline namespace ${SPS_ABI_NAMESPACE_NAME} {")
  set(SPS_ABI_NAMESPACE_END "}")
endif ()
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/spsABINamespace.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/spsABINamespace.h"
  @ONLY)

set(SpsCommonCore_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsCommonCore_BUILD_TESTING ${BUILD_TESTING})

# TODO: Get this from .git
configure_file(spsVersionFull.h.in spsVersionFull.h)
configure_file(spsVersionMacros.h.in spsVersionMacros.h)

set(classes
  spsVersion
)

if(DEFINED VTK_MODULE_ENABLE_SPS_CommonCore)
  vtk_module_add_module(SPS::CommonCore
    CLASSES           ${classes}
    NOWRAP_CLASSES    ${nowrap_classes}
    SOURCES           ${sources}
    HEADERS           ${headers}
    TEMPLATE_CLASSES  ${template_classes}
    PRIVATE_TEMPLATES ${private_templates}
    HEADERS_SUBDIR    "")
  vtk_module_link(SPS::CommonCore
    PRIVATE
    VTK::CommonCore)
endif()
