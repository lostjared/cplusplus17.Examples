#include<iostream>

// using fold expression
template<typename... T>
auto addEmUp(T... x) {
    return (... + x);
}

int main() {
    int value = addEmUp(10, 20, 30)/3;
    std::cout << "10+20+30/3 = is: " << value << "\n";
    return 0;
}
