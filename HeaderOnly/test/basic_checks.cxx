#include <sps/functional.hpp>

int main(int argc, char* argv[])
{

  volatile size_t state = 0;
  struct State {
    size_t a, b, c;
  };
  State state2 = {0, 0, 0};

  size_t i = 2;
  myLib::Function<void()> fun = [&state, state2, i]() { state = i; };
  fun();
  return 0;
}
