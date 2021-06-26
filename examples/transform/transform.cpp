#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

std::vector<int> half(std::vector<int> values) {
  transform(values.begin(), values.end(), values.begin(), [](int v) { return v/2; });
    return values;
}

int main(int argc, char **argv) {
    std::vector<int> v { 2,4,6,8, 24,36,96 };
    std::vector<int> v2 = half(v);
    for (auto &i : v2) {
        std::cout << "value: " << i << "\n";
    }
    return 0;
}
