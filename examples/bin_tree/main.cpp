#include"tree.hpp"
#include<iostream>
#include<algorithm>

int main() {
    try {
        tree::Tree<std::string> values;
        while(1) {
        	std::string keyval, value;
        	std::cout << "Enter key: ";
        	std::getline(std::cin, keyval);
            if(keyval == "quit") break;
            std::cout << "Enter value: ";
            std::getline(std::cin, value);
            values.addItem(value, keyval);
            std::cout << "All keys: \n";
            values.printValues();
        }
    } catch(tree::KeyNotFound) {
        std::cerr << "Error key not found, add first..\n";
    }
    return 0;
}

