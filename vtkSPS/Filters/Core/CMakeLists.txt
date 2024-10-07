# Configuration header - not used
set(SpsFiltersCore_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsFiltersCore_BUILD_TESTING ${BUILD_TESTING})

# Create the library
set(classes
  spsCenterOfMass)

if(DEFINED VTK_MODULE_ENABLE_SPS_FiltersCore)
  # When building as a module for VTK 8.90 or later
  vtk_module_add_module(SPS::FiltersCore
    CLASSES           ${classes}
    SOURCES           ${CMAKE_CURRENT_SOURCE_DIR}/vtk.module)
endif()
