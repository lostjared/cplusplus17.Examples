#include<iostream>
#include<string>
#include<vector>

template<typename T, typename... Args>
void insert_List(std::vector<T> &v, Args... args) {
    (v.push_back(args), ...);
}

template<typename Iter>
void printVec(Iter start, Iter stop){
    unsigned int index = 0;
    while(start != stop) {
        std::cout << index << ":\t" << *start << "\n";
        start++;
        index++;
    }
}

int main() {
    std::vector<std::string> values;
    insert_List(values, "Bruni, ", "Jared", "Hello, ", "World", "!");
    printVec(values.begin(), values.end());
    return 0;
}

