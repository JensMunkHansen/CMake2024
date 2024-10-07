include(CMakeDependentOption)

set(SpsCommonDataModel_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsCommonDataModel_BUILD_TESTING ${BUILD_TESTING})

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

  if (0)
    # Example, we can also link in here
    vtk_module_link(SPS::CommonDataModel
      PRIVATE
      VTK::CommonDataModel)
    # Or traditionally (order matters)
    _vtk_module_real_target(REALTARGET SPS::FiltersCore)
    target_include_directories(${REALTARGET} PUBLIC ${EMBREE_INCLUDE_DIRS})
    target_link_libraries(${REALTARGET} PUBLIC ${EMBREE_LIBRARIES})
  endif()
endif()
