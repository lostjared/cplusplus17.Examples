/*
 Calculate Average of an Array at Compile Time
*/
#include<iostream>
#include<string>
#include<cstdlib>

template<typename T, std::size_t size>
constexpr T Average(const T *arr) {
    T total = T();
    for(unsigned int i = 0; i < size; ++i) {
        total += arr[i];
    }
    return total/size;
}

template<typename T, std::size_t size, const T *arr>
class AverageT {
public:
    static constexpr T value = Average<T, size>(arr);
};

constexpr int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int main() {
    constexpr int v = AverageT<int, 10, arr>::value;
    std::cout << "Average calculated at Compile time: " << v << "\n";
    return 0;
}
