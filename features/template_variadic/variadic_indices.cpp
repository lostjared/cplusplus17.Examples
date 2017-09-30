#include<iostream>
#include<vector>

template<typename T>
void print(const T &type) {
    std::cout << type << "\n";
}

template<typename T, typename... Args>
void print(const T &type, Args... args) {
    print(type);
    print(args...);
}

template<typename Container, typename... Index>
void PrintIndex(const Container &c, Index... index) {
    print(c[index]...);
}

int main() {
    std::vector<std::string> v{"Hello, ", " World!", " Jared"};
    PrintIndex(v, 0, 1, 2);
    return 0;
}
