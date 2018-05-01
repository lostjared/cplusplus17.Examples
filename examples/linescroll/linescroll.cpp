#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<thread>
#include<chrono>

int main(int argc, char **argv) {
    if(argc != 3) {
        std::cerr << "Error incorrect arguments\n" << argv[0] << " text delay\n";
        exit(EXIT_FAILURE);
    }
    std::string text = argv[1];
    int time_wait = atoi(argv[2]);
    if(time_wait == 0) {
        std::cerr << "Error please use millisecond delay as second argument...\n";
        exit(EXIT_FAILURE);
    }
    std::fstream file;
    file.open(text, std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error could not open file: " << text << "\n";
        exit(EXIT_FAILURE);
    }
    
    while(!file.eof()) {
        std::string line;
        std::getline(file, line);
        if(file) {
            std::cout << line << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(time_wait));
        }
    }
    file.close();
    return EXIT_SUCCESS;
}
