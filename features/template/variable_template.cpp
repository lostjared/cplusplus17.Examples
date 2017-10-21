#include<iostream>
#include<vector>
#include<unordered_map>

template<typename T>
constexpr T pi = T(3.1415926535897932385L);

template<typename T>
using Vec = std::vector<T>;

template<typename T>
using StringKeyMap = std::unordered_map<std::string, T>;

template<typename T>
T carea(T r) {
    return pi<T> * r * r;
}

template<typename Iter>
void printMap(Iter start, Iter stop) {
    while(start != stop) {
        auto [key,value] = *start;
        std::cout << key << ":" << value << "\n";
        start++;
    }
}

int main() {
    Vec<std::string> v;
    StringKeyMap<int> values;
    float val = carea(10.f);
    std::cout << "Area: " << val << "\n";
    values["test1"] = 1;
    values["test2"] = 2;
    printMap(values.begin(), values.end());
    return 0;
}
