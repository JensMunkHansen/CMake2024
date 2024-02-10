// TODO: When installed, it is Foo/Foo.h, else Foo.h
#include <Deep/Deep.h>
#include <iostream>

int main(int, char*[])
{
  std::cout << Deep::Version() << std::endl;
  return 0;
}
