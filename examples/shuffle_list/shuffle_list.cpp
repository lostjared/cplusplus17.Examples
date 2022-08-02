#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include<chrono>
#include<random>


void read_stream(std::istream &in, std::vector<std::string> &out) {
    while(!in.eof()) {
        std::string s;
        std::getline(in, s);
        if(in)
            out.push_back(s);
    }
}

int main(int argc, char **argv) {
    std::vector<std::string> vec;
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    if(argc == 1) {
        read_stream(std::cin, vec);
    } else if(argc >= 2) {
        for(int i = 1; i < argc; ++i) {
            std::fstream file;
            file.open(argv[i], std::ios::in);
            if(file.is_open())
                read_stream(file, vec);
            else {
                std::cerr << "Error could not read file...\n";
                exit(EXIT_FAILURE);
            }
        }
    }
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
    for(auto &s : vec) {
        std::cout << s << "\n";
    }
    return 0;
}
