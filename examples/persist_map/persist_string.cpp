// Enter quit as key to stop the loop and write to file
#include<iostream>
#include<string>
#include"permap.hpp"

// loop and print items in container
template<typename Iter>
void printMap(Iter start, Iter stop) {
    while(start != stop) {
        auto [first, second] = *start;
        std::cout << first << ":\t" << second << "\n";
        start++;
    }
}

int main() {
    // persist object
    persist::PersistMap<std::string> string_map("strings.dat", persist::StringRead, persist::StringWrite);
    bool active = true;
    while(active) {
        std::string key, value;
        std::cout << "Enter key: ";
        std::getline(std::cin, key);
        if(key == "quit") {
            active = false;
            continue;
        }
        std::cout << "Enter value: ";
        std::getline(std::cin, value);
        string_map[key] = value;
        printMap(string_map->begin(), string_map->end());
    }
    return 0;
}
