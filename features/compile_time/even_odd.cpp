#include<iostream>

constexpr bool isEven(unsigned int n) {
    if((n%2)==0) return true;
    return false;
}

template<int N, bool = isEven(N)>
class Even;


template<int N>
class Even<N, false> {
public:
    static constexpr bool even = false;
    static constexpr unsigned int value = N;
};

template<int N>
class Even<N, true> {
public:
    static constexpr bool even = true;
    static constexpr unsigned int value = N;
};

template<bool value>
class Output {
public:
    void output() {
        if(value == true) {
            std::cout << "Value is even.\n";
        } else {
            std::cout << "Value is odd.\n";
        }
    }
};

Output<Even<1>::even> output1;
Output<Even<2>::even> output2;

int main() {
    output1.output();
    output2.output();
    return 0;
}
