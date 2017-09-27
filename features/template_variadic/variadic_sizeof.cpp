// Will print out argument index for each variable argument
// using sizeof...

#include<iostream>

template<typename T>
void print(int len, const T &type) {
    std::cout << "argument index: " << len << " [" << type << "]\n";
}

template<typename T, typename... Args>
void print(int len, const T &type, Args... args) {
    print(sizeof...(args), type);
    print(0, args...);
}


int main() {
    print(0x0, "Hello, ", "World!", " ", 100, "+", 255, "=", (100+255));
    return 0;
}
