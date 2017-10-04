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

template<bool value, int N>
class Output {
public:
    void output() {
        if(value == true) {
            std::cout << "Value: " << N << " is even.\n";
        } else {
            std::cout << "Value: " << N << " is odd.\n";
        }
    }
};

Output<Even<1>::even, Even<1>::value> output1;
Output<Even<2>::even, Even<2>::value> output2;

int main() {
    output1.output();
    output2.output();
    return 0;
}
