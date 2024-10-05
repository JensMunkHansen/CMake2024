# Test with data

# Test without data
vtk_add_test_cxx(
  spsIOGeneralCxxTests novalid_tests
  TestPolyDataPieceFilter.cxx, NO_VALID)


#  TestPolyDataPieceFilter.cxx2

set(all_tests
  ${novalid_tests})

vtk_test_cxx_executable(spsIOGeneralCxxTests all_tests)
