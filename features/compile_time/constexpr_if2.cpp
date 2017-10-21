#include<iostream>

template<typename T>
void Only64(T type) {
    if constexpr( sizeof(type) > 4) {
        std::cout << "Greater than 4...\n";
    } else {
        std::cout << "Less than equal 4...\n";
    }
}

template<typename T>
class X {
public:
    template<typename T2>
    void f(T2 t) {
        if constexpr(sizeof(t) == sizeof(T)) {
            std::cout << "Same size...\n";
        } else {
            std::cout << "Not equal...\n";
        }
    }
};

template<int val>
class Y {
public:
    void test() {
        if constexpr(val == 55) {
            std::cout << "This code is generated only when val is equal to 55\n";
        } else {
            std::cout << "Otherwise this code is generated..\n";
        }
    }
};

int main() {
    // some different tests
    Only64<unsigned int>(10);
    Only64<unsigned long>(10);
    X<int> x;
    X<long> y;
    int x_x = 10;
    long y_y = 20;
    x.f(y_y);
    x.f(x_x);
    y.f(y_y);
    y.f(x_x);
    Y<55> y_val;
    y_val.test();
    Y<100> y_val2;
    y_val2.test();
    return 0;
}
