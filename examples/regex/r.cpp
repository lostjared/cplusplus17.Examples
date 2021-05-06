#include<iostream>
#include<string>
#include<regex>

int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cerr << "Error requires one argument..\n";
        exit(EXIT_FAILURE);
    }
    while(!std::cin.eof()) {
        std::string s;
        std::getline(std::cin, s);
        std::regex r(argv[1]);
        if(std::cin && std::regex_search(s, r)) {
            std::cout << argv[0] << ": match!\n";
        }
    }
    
    return 0;
}

