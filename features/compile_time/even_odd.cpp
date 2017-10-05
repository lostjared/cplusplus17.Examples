/* Source file shows a few ways
   you can use a compile time check to ensure
   a value is even versus odd.
 
   - Jared Bruni
*/

#include<iostream>
#include<utility>
#include<type_traits>

constexpr bool isEven(unsigned int n) {
    return ((n%2)==0) ? true : false;
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

// will cause a error if value is false
template<bool value>
class Output {
public:
    static_assert((value==true),"value is odd");
    void output() {
        if(value == true) {
            std::cout << "Value is even.\n";
        } else {
            std::cout << "Value is odd.\n";
        }
    }
};

// program will generate a error at compile time
// if you try to pass EvenNumber an odd number
template<int N>
using enable_even = std::enable_if_t<Even<N>::even>;

template<int N, typename = enable_even<N>>
class EvenNumber {
public:
    void printValue() {
        std::cout << "Value is: " << N << "\n";
    }
};

template<int N>
class testIfEven {
public:
    static_assert(isEven(N)==true, "Value is odd");
};

Output<Even<6>::even> output1;
Output<Even<2>::even> output2;
EvenNumber<10> even;
//EvenNumber<7> odd; // error is odd so not found

int main() {
    //Output<Even<3>::even> output3; // will cause compile error because of static assert
    output1.output();
    output2.output();
    even.printValue();
    //testIfEven<9> value; // will cause an error if passed an odd number
    return 0;
}
