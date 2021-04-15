// pipe data to standard output stream
// to produce C++ array of characters
// for stream
// example
// $ cat text.txt | ./stdin_to_bin
// or
// $ cat text.txt | ./stdin_to_bin --lang=python
// Argument Types
// --name [variable name ]
// --type [ variable type ]
// --lang [ python/cpp ]

#include"cmd-switch.hpp"
#include<iostream>
#include<sstream>

int main(int argc, char **argv) {
    
    try {
        
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string cmd_name;
        std::ostringstream stream;
        bool name=argz.extract("--name", cmd_name);
        if(!name)
            cmd_name="array_value";
        std::string type;
        bool type_;
        type_=argz.extract("--type", type);
        
        std::string lang;
        int lang_type = 0;
        argz.extract("--lang",lang);
        if(lang == "python")
            lang_type = 1;
        else if(lang == "php")
            lang_type = 2;
        else if(lang == "js")
            lang_type = 3;
        else if(lang == "perl")
            lang_type = 4;
        else if(lang == "swift")
            lang_type = 5;
        else if(lang == "ruby")
            lang_type = 6;
        else if(lang == "java")
            lang_type = 7;
        else if(lang == "rust")
            lang_type = 8;
        else
            lang_type = 0;
        
        switch(lang_type) {
            case 0: {
            if(!type_)
                type = "unsigned char";
            
            stream << type << " " << cmd_name << " [] = {\n";
            unsigned long count = 0;
            while(!std::cin.eof()) {
                unsigned char c = 0;
                std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                
                int p = std::cin.peek();
                
                if(std::cin) {
                    stream << "0x" << std::hex << static_cast<unsigned int>(static_cast<unsigned char>(c));;
                    if(p != EOF)
                        stream << ", ";
                    ++count;
                }
            }
            stream << ", 0 };\n";
            stream << "unsigned long " << cmd_name << "_count = 0x" << std::hex << count << ";\n";
        }
                break;
        case 1: {
            stream << "$" << cmd_name << " = array(";
                while(!std::cin.eof()) {
                    unsigned char c = 0;
                    std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                    
                    int p = std::cin.peek();
                    
                    if(std::cin) {
                        stream << static_cast<unsigned int>(c);
                        if(p != EOF)
                            stream << ",";
                    }
                }
                stream << ");\n";
        }
                break;
        case 3: {
            stream <<"let " << cmd_name << " = [";
                while(!std::cin.eof()) {
                    unsigned char c = 0;
                    std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                    
                    int p = std::cin.peek();
                    
                    if(std::cin) {
                        stream << static_cast<unsigned int>(c);
                        if(p != EOF)
                            stream << ",";
                    }
                }
                stream << "]\n";
        }
                break;
            case 4: {
                stream << "my @" << cmd_name << " := ";
                while(!std::cin.eof()) {
                    unsigned char c = 0;
                    std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                    
                    int p = std::cin.peek();
                    
                    if(std::cin) {
                        stream << static_cast<unsigned int>(c);
                        if(p != EOF)
                            stream << ",";
                    }
                }
                stream << ";\n";
            }
                break;
            case 5: {
                stream << "var " << cmd_name << " = [";
                while(!std::cin.eof()) {
                    unsigned char c = 0;
                    std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                        int p = std::cin.peek();
                        if(std::cin) {
                            stream << static_cast<unsigned int>(c);
                            if(p != EOF)
                                stream << ",";
                        }
                }
                stream << "]\n";
                
            }
                break;
                
        case 2: {
            stream << cmd_name << " = [";
            while(!std::cin.eof()) {
                unsigned char c = 0;
                std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                
                int p = std::cin.peek();
                
                if(std::cin) {
                    stream << "0x" << std::hex << static_cast<unsigned int>(c);
                    if(p != EOF)
                        stream << ",";
                }
            }
            stream << "]\n";
        }
        break;
        case 6: {
                stream << cmd_name << " = Array[";
                while(!std::cin.eof()) {
                    unsigned char c = 0;
                    std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                    
                    int p = std::cin.peek();
                    
                    if(std::cin) {
                        stream << static_cast<unsigned int>(c);
                        if(p != EOF)
                            stream << ",";
                    }
                }
                stream << "]\n";
        }
        break;
        case 7: {
                stream << "byte[] " << cmd_name << " = { ";
                unsigned long count = 0;
                while(!std::cin.eof()) {
                    unsigned char c = 0;
                    std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                    int p = std::cin.peek();
                    if(std::cin) {
                        stream << "0x" << std::hex << static_cast<unsigned int>(static_cast<unsigned char>(c));;
                        if(p != EOF)
                            stream << ", ";
                        ++count;
                    }
                }
                stream << ", 0 };\n";
                stream << "long " << cmd_name << "_count = 0x" << std::hex << count << ";\n";
            }
                break;
            case 8: {
                stream << "let " << cmd_name << " = [";
                while(!std::cin.eof()) {
                    unsigned char c = 0;
                    std::cin.read(reinterpret_cast<char*>(&c),sizeof(c));
                    
                    int p = std::cin.peek();
                    
                    if(std::cin) {
                        stream << static_cast<unsigned int>(c);
                        if(p != EOF)
                            stream << ",";
                    }
                }
                stream << "];";

            }
                break;
        }
        std::cout << stream.str() << "\n";
    }
    catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
