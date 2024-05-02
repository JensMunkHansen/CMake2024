#include <sps/functional.hpp>


void fun() {

}
int main(int argc, char* argv[])
{
  auto p = myLib::Function<void(void)>(fun);
  return 0;
}
