#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_version.hpp>

#include <sps/functional>
#include <iostream>

TEST_CASE("sample test", "[ctor]")
{
  std::cout << Catch::libraryVersion() << std::endl;
  //  std::cout << Catch::libraryVersion() << std::endl;
  volatile size_t state = 0;
  struct State {
    size_t a, b, c;
  };
  State state2 = {0, 0, 0};

  size_t i = 2;
  sps::stack_function<void()> fun = [&state, state2, i]() { state = i; };
  fun();
  REQUIRE(0 == 0);
}
