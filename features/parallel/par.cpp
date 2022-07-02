#include<iostream>
#include<vector>
#include<execution>


int main() {
    std::vector<int> v;
    v.reserve(100);
    for(int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    for_each(std::execution::par, v.begin(), v.end(), [](auto &i) {
        std::cout << i << "\n";
    });
    return 0;
}
