// pipe data to standard output stream
// to produce C++ array of characters
// for stream
// example
// $ cat text.txt | ./stdin_to_bin

#include"cmd-switch.hpp"
#include<iostream>


int main(int argc, char **argv) {
    std::cout << "unsigned char array[] = {\n";
    int count = 0;
    while(!std::cin.eof()) {
        unsigned char c = std::cin.get();
        if(std::cin) {
            std::cout << "0x" << std::hex << (unsigned int)(unsigned char)c << ",";
            ++count;
        }
    }
    std::cout << "\n0 };\n";
    std::cout << "unsigned int array_count = 0x" << std::hex << count << ";\n";
    
    return 0;
}
