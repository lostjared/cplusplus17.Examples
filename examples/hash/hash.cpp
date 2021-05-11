// Just practicing some different ideas and concepts
// chained hash table
// mixing different stuff

#include<iostream>
#include<string>
#include<list>

#include "hash.hpp"


int main(int argc, char **argv) {
    htable::Table<std::string, 1024> table;
    while(1) {
        std::string key;
        std::string value;
        std::cout << "enter key: ";
        std::getline(std::cin, key);
        std::cout << "enter value: ";
        std::getline(std::cin, value);
        table[key] = value;
        // print table
        std::cout << "*****\tprint table\n";
        for(unsigned int i = 0; i < table.size(); ++i) {
            if(table.at(i).size() > 0) {
                for(auto it = table.at(i).begin(); it != table.at(i).end(); ++it) {
                    std::cout << "hash:" << i << " -> " << it->first << ":" << it->second << "\n";
                }
            }
        }
    }
    return 0;
}
