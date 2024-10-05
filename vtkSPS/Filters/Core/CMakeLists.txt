# Configuration header - not used
set(SpsFiltersCore_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsFiltersCore_BUILD_TESTING ${BUILD_TESTING})

# Only needed for old compiler support - not used here
set(SpsFiltersCore_OVERRIDE " override")
set(SpsFiltersCore_DELETE " = delete")

# Create the library
set(classes
  spsCenterOfMass)

# TODO: Figure out how to include header without wrapping to Python!!!!
set(headers)

if(DEFINED VTK_MODULE_ENABLE_SPS_FiltersCore)
  # When building as a module for VTK 8.90 or later
  vtk_module_add_module(SPS::FiltersCore
    CLASSES           ${classes}
    SOURCES           ${CMAKE_CURRENT_SOURCE_DIR}/vtk.module
    HEADERS           ${headers})
  vtk_module_link(SPS::FiltersCore
    PRIVATE
    VTK::FiltersCore)  
endif()
