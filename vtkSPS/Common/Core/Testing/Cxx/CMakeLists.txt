if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  set(_vtk_test_cxx_wasm_enabled_in_browser ON)
  set(_vtk_test_emscripten_extra_linker_args
    "-sASYNCIFY=1"
    "-sASYNCIFY_STACK_SIZE=81920" #~297 nesting levels
    # O2 or higher make wasm-opt terribly slow.
    # test executables take a minute to link.
    "-O2"
    "-g2"
    # we need emscripten to emit code that handles exit code and atexit(s)
    "-sEXIT_RUNTIME=1"
    "-sALLOW_MEMORY_GROWTH=1")
endif ()
vtk_add_test_cxx(spsCommonCoreCxxTests no_valid_tests
  NO_VALID
  TestVersion.cxx
)

set(all_tests
  ${no_valid_tests}
)

vtk_test_cxx_executable(spsCommonCoreCxxTests all_tests)
