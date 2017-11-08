/*
 
 Modified example from "C++ Templates the Complete Guide: Second Edition
 														pg. 530
 
*/


#include<iostream>
#include<string>
#include<cstdlib>
#include<array>

constexpr std::size_t SQRT_VALUE=10;

template<typename T>
constexpr T my_sqrt(T x) {
    if(x <= 1)
        return x;
    
    T lo = 0, hi = x;
    while(1) {
        auto mid = (hi+lo)/2, midSquared= mid*mid;
        if(lo+1 >= hi || midSquared == x) {
            return mid;
        }
        if(midSquared < x) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
}

int main() {
    constexpr auto sqrt_val = my_sqrt(SQRT_VALUE);
    // size of array is determined by calculating the square root of 10
    // at compile time
    std::array<int, sqrt_val> arr;
    for(unsigned int i = 0; i < sqrt_val; ++i) {
        arr[i] = 1;
    }
    std::cout << "Sqrt Value: " << sqrt_val << "\n";
    return 0;
}
