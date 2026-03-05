#include<iostream>
#include<vector>

template<typename T1, typename T2>
class isOfType {
public:
    static constexpr bool value = false;
};

template<typename T>
class isOfType<T,T> {
public:
    static constexpr bool value = true;
};

template<typename T>
void testType(T) {
    if(isOfType<T, int>::value) {
        std::cout << "value is of type int...\n";
    } else if(isOfType<T, float>::value) {
        std::cout << "value is of type float...\n";
    } else {
        std::cout << "value is of type (typeid): " << typeid(T).name() << "\n";
    }
}

template<typename T, typename... Args>
void testType(T value, Args... args) {
    testType(value);
    testType(args...);
}

int main() {
    testType(50, 100, 0.5f, 0.1f, 100u, std::vector<int>());
    return 0;
}
