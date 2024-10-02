include(CMakeDependentOption)

set(SpsCommonDataModel_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsCommonDataModel_BUILD_TESTING ${BUILD_TESTING})

# Only needed for old compiler support - not used here
set(SpsCommonDataModel_OVERRIDE " override")
set(SpsCommonDataModel_DELETE " = delete")

set(classes
  spsDummy
)

if(DEFINED VTK_MODULE_ENABLE_SPS_CommonDataModel)
  vtk_module_add_module(SPS::CommonDataModel
    CLASSES           ${classes}
    SOURCES           ${CMAKE_CURRENT_SOURCE_DIR}/vtk.module
    TEMPLATE_CLASSES  ${template_classes}
    HEADERS           ${headers}
    PRIVATE_TEMPLATES ${private_templates})
endif()
