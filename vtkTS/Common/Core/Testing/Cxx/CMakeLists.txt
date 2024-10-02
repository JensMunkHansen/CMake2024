vtk_add_test_cxx(tsCommonCoreCxxTests no_valid_tests
  NO_VALID
  TestVersion.cxx
)

set(all_tests
  ${no_valid_tests}
)

vtk_test_cxx_executable(tsCommonCoreCxxTests all_tests)
