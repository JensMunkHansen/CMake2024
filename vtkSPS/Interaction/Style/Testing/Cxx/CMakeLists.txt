# Test with data

# Test without data
vtk_add_test_cxx(
  spsInteractionStyleCxxTests data_tests
  TestInteractorStylePainBrush.cxx
)


#  TestPolyDataPieceFilter.cxx2

set(all_tests
  ${data_tests}
)

vtk_test_cxx_executable(spsInteractionStyleCxxTests all_tests
  DISABLE_FLOATING_POINT_EXCEPTIONS
  RENDERING_FACTORY
)
