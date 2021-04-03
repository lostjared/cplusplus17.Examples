#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include"cmd-switch.hpp"

int main(int argc, char **argv) {
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string filename;
        argz.require("--file", filename);
        std::string sep_str;
        bool line_sep=argz.extract("--sep", sep_str);
        std::fstream file;
        file.open(filename, std::ios::in);
        if(!file.is_open()) {
            std::cerr << "Error could not open file: "<< argv[1] << "\n";
            exit(EXIT_FAILURE);
        }
        unsigned int index = 1;
        std::string sep = sep_str+" ";
        if(line_sep == false)
            sep = " ";
        
        while(!file.eof()) {
            std::string line;
            std::getline(file, line);
            if(file)
                std::cout << index++ << sep << line << "\n";
        }
        file.close();
        exit(EXIT_SUCCESS);
    }
    catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
