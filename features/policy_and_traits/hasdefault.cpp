// written by Jared Bruni
#include<iostream>
#include<string>
#include<type_traits>

// will be able to tell us whether or not a type has a default constructor
template<typename T>
class HasDefaultConstructor {
private:
    template<typename T1, typename = decltype(T1())>
    static std::true_type test(void*);
    
    template<typename>
    static std::false_type test(...);
public:
    static constexpr bool value = std::is_same<decltype(test<T>(nullptr)), std::true_type>::value;
};

class X {
public:
    X() = default;
};

class Y {
public:
    Y() = delete;
    Y(int) {}
};

class Z {
public:
    Z() = default;
};

template<typename T>
void PrintOut(T type) {
    if(HasDefaultConstructor<T>::value) {
        std::cout << "Has Default Constructor...\n";
    } else {
        std::cout << "Doesn't have Default Constructor...\n";
    }
}

int main() {
    PrintOut(X()); // true
    PrintOut(Y(int())); // false
    PrintOut(Z());// true
    return 0;
}
