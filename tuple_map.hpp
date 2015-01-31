#ifndef _tuple_map_hpp_
#define _tuple_map_hpp_

#include "int_list.hpp"
#include <tuple>

template<int I, typename T, typename F>
auto mapped_item(const T& t, const F& f) {
	return f(std::get<I>(t));
}

template<int ...I, typename T, typename F>
auto tuple_map_impl(int_list<I...>, const T& t, const F& f) {
	return std::make_tuple(mapped_item<I>(t, f)...);
}

template<typename ...T, typename F>
auto tuple_map(const std::tuple<T...>& t, const F& f) {
	return tuple_map_impl(make_int_list<0, sizeof...(T)>(), t, f);
}

#endif//_tuple_map_hpp_