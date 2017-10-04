#include<iostream>

constexpr bool is_Prime(unsigned int p) {
    for(unsigned int d=2; d<=p/2; ++d) {
        if((p%d) == 0)
            return false;
    }
    return p > 1;
}

// calculate at run time whether 9 is prime or not
constexpr bool ninePrime = is_Prime(9);


template<int N, bool = is_Prime(N)>
struct Prime;

template<int N>
struct Prime<N, false> {
    void print() { std::cout << "Value: " << N << " is not Prime..\n"; }
};

template<int N>
struct Prime<N, true> {
    void print() { std::cout << "Value: " << N << " is prime..\n"; }
};

Prime<7> number; // calculate at compile time

int main() {
    number.print();
    // calculate at runtime
    for(unsigned int i = 0; i <= 100; ++i) {
        if(is_Prime(i)==true)
            std::cout << "Value: " << i << " is prime.\n";
        else
            std::cout << "Value: " << i << " is not prime.\n";
    }
    return 0;
}
