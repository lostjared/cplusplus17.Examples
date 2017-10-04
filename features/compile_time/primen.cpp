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
    void print() { std::cout << "Value: " << N << " is not Prime..\n"; }
};

template<int N>
class Prime<N, true> {
public:
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
