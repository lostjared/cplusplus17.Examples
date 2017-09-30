/* Concept from "C++ Templates the Complete Guide: Second Edition
   Chapter 6
 */


#include<iostream>
#include<utility>

class TypeValue {};

void type(TypeValue &c) {
    std::cout << "passed value: TypeValue &c\n";
}

void type(TypeValue &&c) {
    std::cout << "passed value: TypeValue &&c\n";
}

void type(const TypeValue &c) {
    std::cout << "passed value: const TypeValue &c\n";
}

template<typename T>
void pass(T&& value) {
    type(std::forward<T>(value));
}

int main() {
    TypeValue t1;
    const TypeValue t2;
    pass(t1);// calls &
    pass(t2);// calls const &
    pass(std::move(t1));// calls &&
    return 0;
}
