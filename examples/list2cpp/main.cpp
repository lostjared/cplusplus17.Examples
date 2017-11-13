#include<iostream>
#include<string>
#include"list2cpp.hpp"

int main(int argc, char **argv) {
    if(argc != 5) {
        std::cerr << "Requires two arguments file output varname type\n";
        exit(EXIT_FAILURE);
    }
    lst::OutputList str_list;
    if(str_list.addFile(argv[1])) {
        lst::ListType listvar;
        if(argv[4][0] == 'c')
            listvar = lst::ListType::CHAR;
        else
            listvar = lst::ListType::STRING;
        
        if(str_list.outputToFile(argv[2],argv[3], listvar)) {
            std::cout << "Sucessfully output list to: " << argv[2] << "\n";
        } else {
            std::cout << "Encountered an error..\n";
        }
    }
    return 0;
}
