// some different ways you can use
// auto in C++17

#include<iostream>

// some value
template<typename T>
class X {
public:
    X(T type) : value(type) {}
    T value;
    void print() { std::cout << "value is: " << value << "\n"; }
    float get() { return static_cast<float>(value); }
};

// auto return type
auto function() {
    X<int> x(200);
    x.print();
    return x;
}

// auto for template parameter
template<auto S>
class Y {
public:
    int values[S];
    int &operator[](unsigned int i) { return values[i]; }
};


// return type based off type passed in
template<typename T>
auto function2(T t) -> decltype(t.get()) {
    t.print();
    return t.get()+0.7f;
}

int main() {
    // some different ways you can use auto
    // set x is integer
    auto x = 100;
    // x is float
    auto y = 45.2f;
    // z is X<int>
    auto z = X<int>(x);
    z.print();
    // f is X<int>
    auto f = function();
    f.print();
    // value is float
    auto value = function2<X<int>>(f);
    std::cout << "float value: " << value << "\n";
    // Y array of 3 with overloaded []
    Y<3> values;
    values[0] = 4;
    values[1] = 2;
    values[2] = 8;
    // range for loop using auto
    for(auto &index : values.values) {
        std::cout << "arr value: " << index << "\n";
    }
    // arguments from array
    auto &[ax,ay,az] = values.values;
    ax = 100;
    std::cout << "Set value to: " << values[0] << "\n";
    return 0;
}
