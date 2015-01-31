#ifndef _new_tuple_cat_hpp_
#define _new_tuple_cat_hpp_

#include "int_list.hpp"
#include <tuple>

template<typename ...T>
struct total_tuple_size {
   static const int value = 0;
};
 
template<typename ...T, typename ...Rest>
struct total_tuple_size<std::tuple<T...>, Rest...> {
   static const int value = sizeof...(T) + total_tuple_size<Rest...>::value;
};

template<int I, typename T, typename ...Rest>
auto get_value_at_impl(int_list<1>, const T& t, const Rest&... rest) {
   return std::get<I>(t);
}
 
template<int I, typename ...T, typename ...Rest>
auto get_value_at(const std::tuple<T...>& t, const Rest&... rest);
 
template<int I, typename ...T, typename ...Rest>
auto get_value_at_impl(int_list<0>, const std::tuple<T...>& t, const Rest&... rest) {
   return get_value_at<I - sizeof...(T)>(rest...);
}
 
template<int I, typename ...T, typename ...Rest>
auto get_value_at(const std::tuple<T...>& t, const Rest&... rest) {
   return get_value_at_impl<I>(int_list<I < sizeof...(T)>(), t, rest...);
}
 
template<int ...I, typename T, typename ...Rest>
auto tuple_cat_impl(int_list<I...>, const T& t, const Rest&... rest) {
   return std::make_tuple(get_value_at<I>(t, rest...)...);
}
 
template<typename T, typename ...Rest>
auto new_tuple_cat(const T& t, const Rest&... rest) {
   return tuple_cat_impl(make_int_list<0, total_tuple_size<T, Rest...>::value>(), t, rest...);
}

#endif//_new_tuple_cat_hpp_
