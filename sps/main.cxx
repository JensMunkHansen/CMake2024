#include <sps/zip.hpp>
#include <array>
#include <vector>
#include <tuple>
#include <utility>
#include <iterator>
#include <algorithm>
#include <iostream>

// #include <ranges>


int main()
{
  std::list<int> v1 {1, 2, 3, 4, 5}; // 5
  std::array<double, 3> v2 {6.01, 7.02, 8.03}; // 3
  std::vector<short> v3 {22, 850, 29, 3}; // 4
    
  auto zipped = zip(v1, v2, v3);

  for (auto tup: zipped)
    std::cout << '(' << std::get<2>(tup) << ", " << std::get<1>(tup) << ") ";

  //    std::sort(zipped.begin(), zipped.end(), [](auto& a, auto& b) {return std::get<2>(a) > std::get<2>(b);});
  std::sort(zipped.begin(), zipped.end(), [](auto& a, auto& b) {return std::get<2>(a) < std::get<2>(b);});
  //std::ranges::sort(zipped, [](const auto& a, const auto& b) {return std::get<2>(a) > std::get<2>(b);});

  std::cout << std::get<0>(*zipped.begin()) << std::endl;
}
