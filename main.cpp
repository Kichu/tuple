#include "new_tuple_cat.hpp"
#include <iostream>
#include <typeinfo>

int main() {
   auto t1 = std::make_tuple(10, 'a');
   auto t2 = std::make_tuple("hello", 42.0);
   auto t3 = new_tuple_cat(t1, t2);
   std::cout << typeid(t3).name() << std::endl;
   return 0;
}
