#ifndef _int_list_hpp_
#define _int_list_hpp_

template<int ...I>
struct int_list {};
 
template<typename I, int Start, int End>
struct make_int_list_impl;
 
template<int ...I, int Start, int End>
struct make_int_list_impl<int_list<I...>, Start, End> {
   using type = typename make_int_list_impl<int_list<End-(Start+1), I...>, Start, End - 1>::type;
};
 
template<int ...I, int End>
struct make_int_list_impl<int_list<I...>, End, End> {
   using type = int_list<I...>;
};
 
template<int Start, int End>
using make_int_list = typename make_int_list_impl<int_list<>, Start, End>::type;

#endif//_int_list_hpp_
