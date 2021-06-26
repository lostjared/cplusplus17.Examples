#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

std::vector<int> half(std::vector<int> values) {
    std::transform(values.begin(), values.end(), values.begin(), [](int v) { return v/2; });
    return values;
}

// generic
template<typename Iter>
void half_gen(Iter start, Iter stop) {
    std::transform(start, stop, start, [](auto v) { return v/2; });
}

int main(int argc, char **argv) {
    std::vector<int> v { 2,4,6,8, 24,36,96 };
    std::vector<int> v2 = half(v);
    std::for_each(v2.begin(), v2.end(), [](int i) {
        std::cout << "value: " << i << "\n";
    });
    std::vector<double> v3 { 1.5, 2.6, 3.7, 4.9, 5.2 };
    half_gen(v3.begin(), v3.end());
    std::for_each(v3.begin(), v3.end(), [](double d) {
        std::cout << "value: " << d << "\n";
    });
    return 0;
}
