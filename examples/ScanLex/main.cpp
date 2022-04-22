#include "scan_lex.hpp"


#include<fstream>

int main(int argc, char **argv) {

    if(argc == 1) {
        while(1) {
            try {
                std::cout << "=)> ";
                std::string text;
                std::getline(std::cin, text);
                scan::Scanner scanner(text);
                scanner.scan();
                scanner.print();
            } catch(scan::ScanException &e) {
                std::cerr << e.error() << "\n";
            }
        }
    } else if(argc == 2) {
        try {
            char *buf;
            std::fstream file;
            file.open(argv[1], std::ios::in);
            if(!file.is_open()) {
                std::cerr << argv[0] << ": could not open file: " << argv[1] << "\n";
                return -1;
            }
            file.seekg(0, std::ios::end);
            unsigned int len = file.tellg();
            file.seekg(0, std::ios::beg);
            buf = new char [len + 1];
            file.read(buf, len);
            buf[len] = 0;
            std::string text = buf;
            delete [] buf;
            scan::Scanner scanner(text);
            scanner.scan();
            scanner.print();
            scanner.crunch(std::cout);
        } 
         catch(scan::ScanException &e) {
                std::cerr << e.error() << "\n";
         }
    } else if(argc == 3 && std::string(argv[2]) != "-u") {
        try {
            char *buf;
            std::fstream file;
            file.open(argv[1], std::ios::in);
            if(!file.is_open()) {
                std::cerr << argv[0] << ": could not open file: " << argv[1] << "\n";
                return -1;
            }
            file.seekg(0, std::ios::end);
            unsigned int len = file.tellg();
            file.seekg(0, std::ios::beg);
            buf = new char [len + 1];
            file.read(buf, len);
            buf[len] = 0;
            std::string text = buf;
            delete [] buf;
            scan::Scanner scanner(text);
            scanner.scan();
            scanner.print();
            std::fstream out;
            out.open(argv[2], std::ios::out | std::ios::binary);
            if(!out.is_open()) {
                std::cerr << argv[0] << ": could not open output file.\n";
                return -1;
            }
            crunch(&scanner, out);
            out.close();
        } 
        catch(scan::ScanException &e) {
                std::cerr << e.error() << "\n";
        }
    } else if(argc == 3 && std::string(argv[2]) == "-u") {
            std::fstream file;
            file.open(argv[1], std::ios::in | std::ios::binary);
            scan::uncrunch(file);
            file.close();
    }   

    return 0;
}