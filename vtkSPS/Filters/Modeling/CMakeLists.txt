# Configuration header - not used
set(SpsFiltersModeling_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsFiltersModeling_BUILD_TESTING ${BUILD_TESTING})

# Only needed for old compiler support - not used here
set(SpsFiltersModeling_OVERRIDE " override")
set(SpsFiltersModeling_DELETE " = delete")

# Create the library
set(classes
  spsSimpleTriangleSubdivisionFilter
)

# TODO: Figure out how to include header without wrapping to Python!!!!
set(headers)

if(DEFINED VTK_MODULE_ENABLE_SPS_FiltersModeling)
  # When building as a module for VTK 8.90 or later
  vtk_module_add_module(SPS::FiltersModeling
    CLASSES           ${classes}
    SOURCES           ${CMAKE_CURRENT_SOURCE_DIR}/vtk.module
    HEADERS           ${headers})
endif()
