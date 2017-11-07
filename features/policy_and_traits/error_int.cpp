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
class ErrorInt {
public:
    static_assert(isOfType<T, int>::value == false, "Error int not supported for this type");
};

int main() {
    ErrorInt<char> value1;
    ErrorInt<long> value2;
    // uncomment below to for it cause an error
    // ErrorInt<int> err;
    return 0;
}
