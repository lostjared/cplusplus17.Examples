#include<iostream>

template<typename T>
void echo(const T &value) {
    std::cout << value;
}

template<typename T, typename... Types>
void echo(const T &first, Types... args) {
    echo(first);
    echo(args...);
}

int main() {
    echo("Hello, ", " World! \n", 100, "+", 200, "=", 300, "\n");
    return 0;
}
