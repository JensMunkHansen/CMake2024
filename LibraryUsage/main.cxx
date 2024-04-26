// TODO: When installed, it is Foo/Foo.h, else Foo.h
#include <Foo/Foo.h>

// Header-only
#include <Bar/Function.hpp>

#include <iostream>

int main(int, char*[])
{
  std::cout << Library::Version() << std::endl;

  // Stupid copy-paste code
  volatile size_t state = 0;
  struct State
  {
    size_t a, b, c;
  };
  State state2 = { 0, 0, 0 };

  size_t i = 2;
  myLib::Function<void()> fun = [&state, state2, i]() { state = i; };
  fun();
  
  return 0;
}
