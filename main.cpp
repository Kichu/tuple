#include "new_tuple_cat.hpp"
#include "tuple_map.hpp"
#include "print_tuple.hpp"

#include <iostream>
#include <string>
#include <typeinfo>

void test_tuple_cat() {
   auto t1 = std::make_tuple(10, 'a');
   auto t2 = std::make_tuple("hello", 42.0);
   auto t3 = new_tuple_cat(t1, t2);
   print_tuple(t3);
}

void test_tuple_map() {
	auto t1 = std::make_tuple("Alice", "John", "Sarah");
	auto t2 = tuple_map(t1, [](std::string item) {return "hello" + item;});
    print_tuple(t2);
}

int main() {
    test_tuple_cat();
    test_tuple_map();
    return 0;
}
