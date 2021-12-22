
#include "dmd.hpp"
#include<iostream>

int main(int argc, char **argv) {
    Diamond dmd(argc, argv);
    std::string line;
    while(dmd.next(line)) {
        std::cout << line << "\n";
    }
    return 0;
}
