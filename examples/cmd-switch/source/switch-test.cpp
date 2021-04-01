#include<iostream>
#include"cmd-switch.hpp"
#include<cstdlib>

int main(int argc, char **argv) {
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        if(argz.check("--init") == true) {
            std::cout << "init flag present..\n";
        }
        std::string pass;
        if(argz.check("--pass") == true && argz.require("--password", pass) == true) {
            std::cout << "Password: " << pass << "\n";
        }
        std::string value;
        if(argz.extract("--value", value) == true) {
            std::cout << "value flag extracted: " << value << "\n";
        }
        argz.print();
        std::vector<std::string> lst {"--value"};
        cmd::ArgumentStringList alst(argc, argv);
        if(Argument_FindInList(lst, alst)) {
            std::cout << "Value found..\n";
        }
        
    } catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Success..\n";
    exit(EXIT_SUCCESS);
	return 0;
}
