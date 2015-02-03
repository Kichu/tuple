#include <iostream>
#include <typeinfo>
#include <utility>
#include <tuple>
#include <array>

template<typename T, typename...ForArray>
struct to_tuple; //code by Stephan T. Lavavej in VS 2015

template<typename ...T>
struct to_tuple<std::tuple<T...>> {
   using type = std::tuple<T...>;
};

template<typename T1, typename T2>
struct to_tuple<std::pair<T1, T2> > {
   using type = std::tuple<T1, T2>;
};

template<typename T, size_t Size, typename ...ForArray>
struct to_tuple<std::array<T, Size  >,        ForArray...>
     : to_tuple<std::array<T, Size-1>, T,     ForArray...> {
};

template<typename T, typename  ...ForArray>
struct to_tuple<std::array<T, 0>, ForArray...> {
   using type = std::tuple<ForArray...>;
};

template</*typename T not needed for C++14, */int Row, int Col>
struct ij_pair { /*using type = T; not needed for C++14*/
   static const int I = Row;
   static const int J = Col;
};

template<typename Result, int Row, int Col, typename Tuple>
struct ij_pairs;

template<typename ...Result, int Row, int Col, typename T, typename ...Rest>
struct ij_pairs<std::tuple<Result...>, Row, Col, std::tuple<T, Rest...>>
     : ij_pairs<std::tuple<Result..., ij_pair</*T not needed for C++14, */Row, Col>>, Row, Col+1, std::tuple<Rest...>> {
};

template<typename Result, int Row, int Col>
struct ij_pairs<Result, Row, Col,std::tuple<>> {
   using type = Result;
};

template<typename IJPairs, int Row, typename ...Tuples>
struct tuple_cat_impl;

template<typename IJPairs, int Row, typename Tuple, typename ...Rest>
struct tuple_cat_impl<IJPairs, Row, Tuple, Rest...>
     : tuple_cat_impl<typename ij_pairs<IJPairs, Row, 0, Tuple>::type, Row+1, Rest...> {
};

template<typename ...IJPair, int Row>
struct tuple_cat_impl<std::tuple<IJPair...>, Row> { /*using ret = std::tuple<typenameIJPair::type...>; not needed for C++14*/
   template<typename Tuples>
   static auto apply(Tuples&&ts) /*-> ret not needed for C++ 14*/ {
      return std::make_tuple(std::get<IJPair::J>(std::get<IJPair::I>(std::forward<Tuples>(ts)))...);
   }
};

template<typename... Tuples>
auto new_tuple_cat(Tuples&&... ts) /*-> typename tuple_cat_impl<std::tuple<>, 0,typename std::decay<Tuples>::type...>::ret not needed for C++14*/ {
   return tuple_cat_impl<std::tuple<>, 0, typename to_tuple<typename std::decay<Tuples>::type>::type...>::apply(std::forward_as_tuple(std::forward<Tuples>(ts)...));
}

int main() {
   auto t0 = new_tuple_cat();
   std::cout << typeid(t0).name() << std::endl;

   auto t1 = std::make_pair(10, 'a');
   auto t2 = std::make_tuple("hello", 42.0);
   auto t3 = std::array<int, 5>();
   auto t4 = new_tuple_cat(t1, t2, t3);
   std::cout << typeid(t4).name() << std::endl;

   return 0;
}
