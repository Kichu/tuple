#ifndef _print_tuple_hpp_
#define _print_tuple_hpp_

#include <tuple>
#include <iostream>

template<int I, typename... T>
void print_tuple_impl(int_list<I>, const std::tuple<T...>& t) {
	print_tuple_impl(int_list<I-1>(), t);
	std::cout << " " << std::get<I>(t);
}

template<typename... T>
void print_tuple_impl(int_list<0>, const std::tuple<T...>& t) {
	std::cout << std::get<0>(t);
}

template<typename... T>
void print_tuple(const std::tuple<T...>& t) {
	print_tuple_impl(int_list<sizeof...(T)-1>(), t);
	std::cout << std::endl;
}

#endif//_print_tuple_hpp_
