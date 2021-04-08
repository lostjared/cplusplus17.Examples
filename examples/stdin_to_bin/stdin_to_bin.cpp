// pipe data to standard output stream
// to produce C++ array of characters
// for stream
// example
// $ cat text.txt | ./stdin_to_bin

#include"cmd-switch.hpp"
#include<iostream>


int main(int argc, char **argv) {
    
    try {
        
        std::cout << "unsigned char array[] = {\n";
        unsigned long count = 0;
        while(!std::cin.eof()) {
            unsigned char c = std::cin.get();
            if(std::cin) {
                std::cout << "0x" << std::hex << static_cast<unsigned int>(static_cast<unsigned char>(c)) << ",";
                ++count;
            }
        }
        std::cout << "\n0 };\n";
        std::cout << "unsigned long array_count = 0x" << std::hex << count << ";\n";
        
    }
    catch(cmd::ArgExcep<std::sttring> &e) {
        std::cerr << e.what() << "\N":
    }
    return 0;
}
