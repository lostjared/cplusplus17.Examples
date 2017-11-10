/*
 
 Parse array of characters into a integer at compile time
 example modified from "C++ Templates the Complete Guide Second Edition"
 Chapter 25, page 600
 
*/


#include<iostream>
#include<string>
#include<cassert>
#include<array>

constexpr int toInt(char c) {
    if (c >= 'A' && c <= 'F')
        return static_cast<int>(c) - static_cast<int>('A') + 10;
    if (c >= 'a' && c <= 'f')
        return static_cast<int>(c) - static_cast<int>('a') + 10;
    
    assert(c >= '0' && c <= '9');
    return static_cast<int>(c) - static_cast<int>('0');
}

template<std::size_t N>
constexpr int parseInt(const char (&arr)[N]) {
    int base = 10;
    int offset = 0;
    
    if(N > 2 && arr[0] == '0') {
        switch(arr[1]) {
            case 'x':
            case 'X':
                base = 16;
                offset = 2;
                break;
            case 'b':
            case 'B':
                base = 2;
                offset = 2;
                break;
            default:
                base = 8;
                offset = 1;
                break;
        }
    }
    int value = 0;
    int multiplier = 1;
    for(std::size_t i = 0; (i < N-offset); ++i) {
        if(arr[N-1-i] != '\'') {
            value += toInt(arr[N-1-i]) * multiplier;
            multiplier *= base;
        }
    }
    return value;
}

int main() {
    constexpr char ch[] = {'1', '0', '0'};
    // parse integer to use as size of array
    std::array<int, parseInt(ch)> arr;
    std::cout << "Array sized to: " << arr.size() << "\n";
    return 0;
}
