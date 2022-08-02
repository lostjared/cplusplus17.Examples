#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include<chrono>
#include<random>


int main(int argc, char **argv) {
    std::vector<std::string> vec;
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    while(!std::cin.eof()) {
        std::string s;
        std::getline(std::cin, s);
        if(std::cin)
            vec.push_back(s);
    }
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
    for(auto &s : vec) {
        std::cout << s << "\n";
    }
    return 0;
}
