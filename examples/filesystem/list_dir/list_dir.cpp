#include<iostream>
#include<string>
#include<filesystem>

int main(int argc, char **argv) {
    if(argc == 1) {
        std::cerr << argv[0] << " directory \n";
        std::cerr << argv[0] << " directory -r (recursive)\n";
        return 0;
    }
    if(argc == 3 && std::string(argv[2]) == "-r") {
        std::filesystem::path p{argv[1]};
        if(is_directory(p)) {
            for(auto &i : std::filesystem::recursive_directory_iterator(argv[1])) {
                std::cout << i.path() << "\n";
            }
        } else {
            std::cerr << "invalid input..\n";
        }
    }
    if(argc == 2) {
        std::filesystem::path p{argv[1]};
        if(is_directory(p)) {
            for(auto &i : std::filesystem::directory_iterator(argv[1])) {
                std::cout << i.path() << "\n";
            }
        } else {
            std::cerr << "invalid input..\n";
        }
    }
    return 0;
}
