// using the is_Prime constexpr function
// at compile time, and at runtime

#include<iostream>

constexpr bool is_Prime(unsigned int p) {
    for(unsigned int d=2; d<=p/2; ++d) {
        if((p%d) == 0)
            return false;
    }
    return p > 1;
}

template<int N, bool = is_Prime(N)>
class Prime;

template<int N>
class Prime<N, false> {
public:
    static constexpr bool value = false;
    void print() {
        std::cout << N << " is not prime\n";
    }
};

template<int N>
class Prime<N, true> {
public:
    static constexpr bool value = true;
    void print() {
        std::cout << N << " is prime\n";
    }
};


static_assert(Prime<7>::value, "Value is not prime");
//static_assert(Prime<9>::value, "Value is not prime"); // will cause compile time error

int main() {
    std::cout << "Prime Numbers 1-100\n";
    for(unsigned int i = 0; i < 100; ++i) {
        if(is_Prime(i)==true)
            std::cout << i << " is prime.\n";
    }
    Prime<13> prime;
    prime.print();
    return 0;
}
