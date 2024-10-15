# Configuration header - not used
set(SpsFiltersGeneral_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsFiltersGeneral_BUILD_TESTING ${BUILD_TESTING})

# Create the library
set(classes
  spsDistancePolyDataFilter
)

if(DEFINED VTK_MODULE_ENABLE_SPS_FiltersGeneral)
  # When building as a module for VTK 8.90 or later
  vtk_module_add_module(SPS::FiltersGeneral
    CLASSES           ${classes}
    SOURCES           ${CMAKE_CURRENT_SOURCE_DIR}/vtk.module)
endif()
