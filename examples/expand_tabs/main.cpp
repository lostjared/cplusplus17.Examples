// Arguments take the form of
// --switch=value
// --file=input-filename
// --num=number of spaces

#include<iostream>
#include<fstream>
#include"cmd-switch.hpp"

int main(int argc, char **argv) {
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string filename;
        argz.require("--file", filename, "input filename");
        std::string num;
        argz.require("--num", num, "number of spaces");
        
        int num_spaces = atoi(num.c_str());
        if(num_spaces <= 0) {
            std::cerr << "Requires Greater than Zero value for spaces.\n";
            exit(EXIT_FAILURE);
        }
        
        std::fstream file;
        file.open(filename, std::ios::in);
        if(!file.is_open()) {
            std::cerr << "Error could not open file: " << filename << "\n";
            exit(EXIT_FAILURE);
        }
        while(!file.eof()) {
            char c = file.get();
            if(c == '\t') {
                for(int i = 0; i < num_spaces; ++i) {
                    std::cout << " ";
                }
            } else {
                std::cout << c;
            }
        }
        file.close();
    } catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
