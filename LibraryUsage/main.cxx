// TODO: When installed, it is Foo/Foo.h, else Foo.h
#include <Foo/Foo.h>
#include <iostream>

int main(int argc, char* argv[])
{
  std::cout << Library::Version() << std::endl;
  return 0;
}
