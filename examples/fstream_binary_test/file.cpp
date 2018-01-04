#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>

enum { ARRAY_SIZE=256 };

struct DataStruct {
    char name_first[ARRAY_SIZE];
    char name_last[ARRAY_SIZE];
    int index;
};

int main(int argc, char **argv) {
    
    if(argc != 3) {
        std::cerr << "Two args expected filename (read or write)\n";
        exit(EXIT_FAILURE);
    }
    
    srand(static_cast<int>(time(0)));

    if(std::string(argv[2]) == "read") {
    	std::fstream file;
        file.open(argv[1], std::ios::in | std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Error could not open file: " << argv[1] << "\n";
            exit(EXIT_FAILURE);
        }
        
        DataStruct ds;
        file.read(reinterpret_cast<char*>(&ds), sizeof(DataStruct));
        std::cout << "Read " << file.gcount() << " bytes.\n";
        std::cout << "Value is: {\n" << ds.name_first << " " << ds.name_last << "\nindex: " << ds.index << "\n}\n";
        file.close();
    } else {
        std::fstream file;
        file.open(argv[1], std::ios::out | std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Error could not open file: " << argv[1] << "\n";
            exit(EXIT_FAILURE);
        }
        DataStruct ds;
        std::string first,last;
        std::cout << "Enter First name: ";
        std::getline(std::cin, first);
        std::cout << "Enter Last name: ";
        std::getline(std::cin, last);
        
        snprintf(ds.name_first, ARRAY_SIZE-1, "%s", first.c_str());
        snprintf(ds.name_last, ARRAY_SIZE-1, "%s", last.c_str());
        ds.index = rand()%255;

        file.write(reinterpret_cast<char*>(&ds), sizeof(DataStruct));
        file.close();
        std::cout << "Wrote to file: " << argv[1] << "\n";
    }

    return 0;
}
