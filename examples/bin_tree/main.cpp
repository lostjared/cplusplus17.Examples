#include"tree.hpp"
#include<iostream>
#include<algorithm>

int main() {
    try {
        tree::Tree<std::string> values;
        std::cout << "Enter Key/Value loop, type quit for key to break loop...\n";
        while(1) {
            std::string keyval, value;
            std::cout << "Enter key: ";
            std::getline(std::cin, keyval);
            if(keyval == "quit") break;
            std::cout << "Enter value: ";
            std::getline(std::cin, value);
            values.addItem(keyval,value);
            std::cout << "All keys: \n";
            values.printValues();
        }
    } catch(tree::KeyNotFound) {
        std::cerr << "Error key not found, add first..\n";
    }
    return 0;
}

