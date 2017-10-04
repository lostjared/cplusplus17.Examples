#include<iostream>

template<typename T, typename... Args>
void println(const T &type, Args... args) {
    std::cout << type;
    if constexpr(sizeof...(args) > 0) // constexpr
        println(args...);
    else
        std::cout << "\n";
}

int main() {
    println("Hello,", " World", "!");
    return 0;
}
