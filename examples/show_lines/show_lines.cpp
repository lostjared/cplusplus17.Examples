#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<fstream>
#include<cstdlib>
#include<vector>

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error could incorrect arguments..\n";
        exit(EXIT_FAILURE);
    }
    
    std::fstream file;
    file.open(argv[1], std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error could not open file...\n";
        exit(EXIT_FAILURE);
    }
    std::stringstream stream;
    stream << file.rdbuf();
    std::vector<std::string> values;
    while(!stream.eof()) {
        std::string s;
        std::getline(stream, s);
        values.push_back(s);
    }
    std::ostringstream s_len;
    s_len << values.size();
    int vlength = s_len.str().size()+1;
    for(int i = 0; i < values.size(); ++i) {
        std::ostringstream strout;
        strout.width(vlength);
        strout.fill('0');
        strout << (i+1);
        std::cout << strout.str() << ": " << values[i] << "\n";
    }
    return 0;
}
