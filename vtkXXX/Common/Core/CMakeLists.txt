include(CMakeDependentOption)

set(TsCommonCore_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(TsCommonCore_BUILD_TESTING ${BUILD_TESTING})

# Only needed for old compiler support - not used here
set(TsCommonCore_OVERRIDE " override")
set(TsCommonCore_DELETE " = delete")

# TODO: Get this from .git
set(TS_BUILD_VERSION 1)
configure_file(tsVersionFull.h.in tsVersionFull.h)
configure_file(tsVersionMacros.h.in tsVersionMacros.h)

set(classes
  tsVersion
)

if(DEFINED VTK_MODULE_ENABLE_TS_CommonCore)
  vtk_module_add_module(TS::CommonCore
    CLASSES           ${classes}
    TEMPLATE_CLASSES  ${template_classes}
    HEADERS           ${headers}
    PRIVATE_TEMPLATES ${private_templates})
  vtk_module_link(TS::CommonCore
    PRIVATE
    VTK::CommonCore)
endif()
