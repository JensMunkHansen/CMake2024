include(CMakeDependentOption)

set(SpsCommonCore_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsCommonCore_BUILD_TESTING ${BUILD_TESTING})

# Only needed for old compiler support - not used here
set(SpsCommonCore_OVERRIDE " override")
set(SpsCommonCore_DELETE " = delete")

# TODO: Get this from .git
set(SPS_BUILD_VERSION 1)
configure_file(spsVersionFull.h.in spsVersionFull.h)
configure_file(spsVersionMacros.h.in spsVersionMacros.h)

set(classes
  spsVersion
)

if(DEFINED VTK_MODULE_ENABLE_SPS_CommonCore)
  vtk_module_add_module(SPS::CommonCore
    CLASSES           ${classes}
    TEMPLATE_CLASSES  ${template_classes}
    HEADERS           ${headers}
    PRIVATE_TEMPLATES ${private_templates})
  vtk_module_link(SPS::CommonCore
    PRIVATE
    VTK::CommonCore)
endif()
