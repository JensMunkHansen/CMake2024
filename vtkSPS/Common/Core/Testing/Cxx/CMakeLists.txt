vtk_add_test_cxx(spsCommonCoreCxxTests no_valid_tests
  NO_VALID
  TestVersion.cxx
)

set(all_tests
  ${no_valid_tests}
)

vtk_test_cxx_executable(spsCommonCoreCxxTests all_tests)
