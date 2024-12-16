sps_add_test_javascript(spsCommonCoreJavaScriptTests no_valid_tests
  NO_VALID
  TestVersion.js
)

set(all_tests
  ${no_valid_tests}
)

sps_test_wasm_executable(spsCommonCoreJavaScriptTests all_tests)
