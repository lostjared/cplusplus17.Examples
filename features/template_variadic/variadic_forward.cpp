#include<iostream>
#include<utility>

template<typename T>
void Print(const T &x) {
    std::cout << "forward: const T&: " << x << "\n";
}

template<typename T>
void Print(T &x) {
    std::cout << "forward: T&: " << x << "\n";
}

template<typename T>
void Print(T &&x) {
    std::cout << "forward: T&&: " << x << "\n";
}

template<typename... Ts>
void Test(Ts&&... xs) {
    Print(std::forward<Ts>(xs)...);
}

int main() {
    int x = 10;
    Test(100);
    Test(x);
    return 0;
}

