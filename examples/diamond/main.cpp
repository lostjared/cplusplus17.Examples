
#include "dmd.hpp"
#include<iostream>

int main(int argc, char **argv) {
    Diamond dmd(argc, argv);
    std::string line;
    while(dmd.next(line)) {
        std::cout << line << "\n";
    }
    dmd.reset();
    while(dmd.next(line)) {
        std::cout << dmd.filename() << ":" << line << "\n";
    }
    return 0;
}
