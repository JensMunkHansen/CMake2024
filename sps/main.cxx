#include <list>
#include <array>
#include <vector>
#include <tuple>
#include <utility>
#include <iterator>
#include <algorithm>
#include <iostream>

#include <ranges>

#if (__cplusplus < 201703L)
// For C++14
namespace detail
{
    template <class F, class Tuple, std::size_t... I>
    constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
    {
        return f(std::get<I>(std::forward<Tuple>(t))...);
    }
}  // namespace detail


template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t)
{
    return detail::apply_impl(
        std::forward<F>(f), std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
}
#else
using std::apply;
#endif

template <typename ...Ranges>
auto zip(Ranges&& ...ranges)
{
    using std::begin; using std::end;

    auto begin_its = std::make_tuple(begin(std::forward<Ranges>(ranges))...);
    auto end_its = std::make_tuple(end(std::forward<Ranges>(ranges))...);

    using vector_elem = std::tuple<std::decay_t<decltype(*begin(std::forward<Ranges>(ranges)))>...>;
    std::vector<vector_elem> result;

    auto size = std::min({std::distance(begin(std::forward<Ranges>(ranges)), end(std::forward<Ranges>(ranges)))...});
    result.reserve(std::size_t(size));

    for(decltype(size) ix = 0; ix < size; ++ix)
    {
        apply([&result](auto&& ...its) mutable
        {
            result.emplace_back(*its...); //No need for redundant `make_tuple`+copy.
        }, begin_its);

        apply([](auto& ...its)
        {
            int unused[] = {0, (++its, 0)...};
        }, begin_its);
    }

    return result;
}

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
