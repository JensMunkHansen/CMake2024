# Test with data

# Test without data
vtk_add_test_cxx(
  spsIOGeneralCxxTests novalid_tests
  TestPolyDataPieceFilter.cxx, NO_VALID)

vtk_add_test_cxx(
  spsIOGeneralCxxTests data_tests
  TestPolyDataPieceFilter2.cxx)


#  TestPolyDataPieceFilter.cxx2

set(all_tests
  ${novalid_tests}
  ${data_tests}
)

vtk_test_cxx_executable(spsIOGeneralCxxTests all_tests
  DISABLE_FLOATING_POINT_EXCEPTIONS
  RENDERING_FACTORY
)
