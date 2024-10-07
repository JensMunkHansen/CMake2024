# Test with data
vtk_add_test_cxx(
  spsFiltersModelingCxxTests data_tests
  TestSimpleTriangleSubdivision.cxx
)

set(all_tests
  ${data_tests}
)

vtk_test_cxx_executable(spsFiltersModelingCxxTests all_tests
  DISABLE_FLOATING_POINT_EXCEPTIONS
  RENDERING_FACTORY
)

