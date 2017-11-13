#include<iostream>
#include<string>
#include"list2cpp.hpp"

int main(int argc, char **argv) {
    if(argc != 5) {
        std::cerr << argv[0] << ": Requires 4 arguments file output varname type (c or s)\n";
        exit(EXIT_FAILURE);
    }
    lst::OutputList str_list;
    if(str_list.addFile(argv[1])) {
        lst::ListType listvar;
        if(argv[4][0] == 'c')
            listvar = lst::ListType::CHAR;
        else
            listvar = lst::ListType::STRING;
        
        if(str_list.validName(argv[3]) == false) {
            std::cerr << "Invalid variable name, must start with a letter and only contain digits and alpha characters.\n";
            exit(EXIT_FAILURE);
        }
        
        if(str_list.outputToFile(argv[2],argv[3], listvar)) {
            std::cout << "Sucessfully output list to: " << argv[2] << "\n";
            std::cout << "Input: " << argv[1] << "\n";
            std::cout << "Output: " << argv[2] << "\n";
            if(listvar == lst::ListType::STRING) {
            	std::cout << "Variables: " << argv[3] << "_arr and " << argv[3] << "_size"<< "\n";
                std::cout << "Varaible type: std::string\n";
            } else {
                std::cout << "Variables: " << argv[3] << "_str and " << argv[3] << "_size"<< "\n";
                std::cout << "Varaible type: const char *\n";
            }
        } else {
            std::cout << "Encountered an error..\n";
        }
    } else {
        std::cerr << "Error could not load list from text file: " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }
    return 0;
}
