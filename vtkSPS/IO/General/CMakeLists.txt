set(SpsIOGeneral_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(SpsIOGeneral_BUILD_TESTING ${BUILD_TESTING})

set(classes
  spsPolyDataPieceFilter
)

vtk_module_add_module(SPS::IOGeneral
  CLASSES ${classes}
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/vtk.module)
