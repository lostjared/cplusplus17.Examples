// pipe data to standard output stream
// to produce C++ array of characters
// for stream
// example
// $ cat text.txt | ./stdin_to_bin

// Argument Types
// --name [variable name ]
// --type [ variable type ]
// --lang [ python/cpp ]

#include"cmd-switch.hpp"
#include<iostream>
#include<sstream>

int main(int argc, char **argv) {
    
    try {
        std::ostringstream stream;
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string cmd_name;
        bool name=argz.extract("--name", cmd_name);
        if(!name)
            cmd_name="array";
        std::string type;
        bool type_;
        type_=argz.extract("--type", type);
        
        bool language_;
        std::string lang;
        int lang_type = 0;
        language_=argz.extract("--lang",lang);
        if(!language_) {
            lang_type = 0;
        }
        if(lang == "python")
            lang_type = 1;
        else
            lang_type = 0;
        
            if(lang_type == 0) {
            if(!type_)
                type = "unsigned char";
            
        
            stream << type << " " << cmd_name << " [] = {\n";
            unsigned long count = 0;
            while(!std::cin.eof()) {
                unsigned char c = 0;
                std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                
                if(std::cin) {
                    stream << "0x" << std::hex << static_cast<unsigned int>(static_cast<unsigned char>(c)) << ",";
                    ++count;
                }
            }
            stream << "\n0 };\n";
            stream << "unsigned long " << cmd_name << "_count = 0x" << std::hex << count << ";\n";
        }
        else {
            stream << cmd_name << " = [";
            while(!std::cin.eof()) {
                unsigned char c = 0;
                std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                
                if(std::cin) {
                    stream <<  static_cast<unsigned int>(c) << ",";
                }
            }
            stream << "0 ]\n";
        }
        std::cout << stream.str().c_str();
    }
    catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
