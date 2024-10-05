set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SpsIOGeneral_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsIOGeneral_BUILD_TESTING ${BUILD_TESTING})

# Only needed for old compiler support - not used here
set(SpsIOGeneral_OVERRIDE " override")
set(SpsIOGeneral_DELETE " = delete")

set(classes
  spsPolyDataPieceFilter
)

vtk_module_add_module(SPS::IOGeneral
  CLASSES ${classes}
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/vtk.module)
