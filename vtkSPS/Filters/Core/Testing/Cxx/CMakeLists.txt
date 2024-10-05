vtk_add_test_cxx(
  spsFiltersCoreCxxTests data_tests)

vtk_add_test_cxx(spsFiltersCoreCxxTests no_valid_tests
  NO_VALID
  TestCenterOfMass.cxx
)  

set(all_tests
  ${data_tests}
  ${no_valid_tests}
)

vtk_test_cxx_executable(spsFiltersCoreCxxTests all_tests)

