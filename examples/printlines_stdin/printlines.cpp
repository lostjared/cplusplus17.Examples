#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>

int main() {
    std::istream &file = std::cin;
    unsigned int index = 1;
    while(!file.eof()) {
        std::string line;
        std::getline(file, line);
        if(file)
            std::cout << index++ << ": " << line << "\n";
    }
    exit(EXIT_SUCCESS);
    return 0;
}
