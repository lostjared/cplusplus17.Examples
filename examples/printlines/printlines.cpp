#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error: requires one argument.\nFile to print..\n";
        exit(EXIT_FAILURE);
    }
    
    std::fstream file;
    file.open(argv[1], std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error could not open file: "<< argv[1] << "\n";
        exit(EXIT_FAILURE);
    }
    unsigned int index = 1;
    while(!file.eof()) {
        std::string line;
        std::getline(file, line);
        if(file)
            std::cout << index++ << ": " << line << "\n";
    }
    file.close();
    exit(EXIT_SUCCESS);
    return 0;
}
