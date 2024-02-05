#include "Foo/Foo.h"
#include <iostream>

int main(int, char*[])
{
  std::cout << Library::Version() << std::endl;
  return 0;
}
