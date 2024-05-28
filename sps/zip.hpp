#include <list>
#include <array>
#include <vector>
#include <tuple>
#include <utility>
#include <iterator>
#include <algorithm>
#include <iostream>

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

