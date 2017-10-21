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
        if(sizeof(t) == sizeof(T)) {
            std::cout << "Same size...\n";
        } else {
            std::cout << "Not equal...\n";
        }
    }
};

int main() {
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
    return 0;
}
