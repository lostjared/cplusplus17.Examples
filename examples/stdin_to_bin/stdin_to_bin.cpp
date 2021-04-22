// pipe data to standard output stream
// to produce array
// from stream
// example
// $ cat text.txt | ./stdin_to_bin
// or
// $ cat text.txt | ./stdin_to_bin --lang=python
// Argument Types
// --term
// add --term to null terminate c++ array
// --name [variable name ]
// --type [ variable type ]
// --lang [ python/cpp/php/js/perl/swift/ruby/rust ]
// Suports Python, PHP, JavaScript, Perl, Swift, Ruby, Java, Rust, C/C++

// Tony the tiger
// getting better at this

#include"cmd-switch.hpp"
#include<iostream>
#include<sstream>

void outputCPP(std::string type, std::string cmd_name, bool term);
void outputPython(std::string cmd_name);
void outputPHP(std::string cmd_name);
void outputJS(std::string cmd_name);
void outputPerl(std::string cmd_name);
void outputSwift(std::string cmd_name);
void outputRuby(std::string name);
void outputJava(std::string cmd_name);
void outputRust(std::string cmd_name);
void outputGo(std::string cmd_name);

int main(int argc, char **argv) {
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string cmd_name;
        std::ostringstream stream;
        bool name=argz.extract("--name", cmd_name);
        bool term=argz.check("--term");
        if(!name)
            cmd_name="array_value";
        std::string type;
        bool type_;
        type_=argz.extract("--type", type);
        std::string lang;
        int lang_type = 0;
        argz.extract("--lang",lang);
        lang = cmd::_tolower(lang);
        if(lang == "python")
            lang_type = 2;
        else if(lang == "php")
            lang_type = 1;
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
        else if(lang == "golang")
            lang_type = 9;
        else
            lang_type = 0;
        
        switch(lang_type) {
        case 0: {
            if(!type_)
                type = "unsigned char";
                outputCPP(type,cmd_name,term);
        }
            break;
        case 1: {
            outputPHP(cmd_name);
        }
            break;
        case 3: {
            outputJS(cmd_name);
        }
            break;
        case 4: {
            outputPerl(cmd_name);
        }
            break;
        case 5: {
            outputSwift(cmd_name);
        }
            break;
        case 2: {
            outputPython(cmd_name);
        }
            break;
        case 6: {
            outputRuby(cmd_name);
        }
            break;
        case 7: {
            outputJava(cmd_name);
        }
            break;
        case 8: {
            outputRust(cmd_name);
        }
            break;
        case 9: {
            outputGo(cmd_name);
        }
            break;
        }
    }
    catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}

void outputCPP(std::string type,std::string cmd_name,bool term) {
    std::ostringstream stream;
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
    if(term)
        stream << ", 0 };\n";
    else
        stream <<"};\n";
    
    stream << "unsigned long " << cmd_name << "_count = 0x" << std::hex << count << ";\n";
    std::cout << stream.str() << "\n";
}
void outputPython(std::string cmd_name) {
    std::ostringstream stream;
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
    std::cout << stream.str() << "\n";
}
void outputPHP(std::string cmd_name) {
    std::ostringstream stream;
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
    std::cout << stream.str() << "\n";
}
void outputRust(std::string cmd_name) {
    std::ostringstream stream;
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
    std::cout << stream.str() << "\n";
}
void outputPerl(std::string cmd_name) {
    std::ostringstream stream;
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
    std::cout << stream.str() << "\n";
}
void outputSwift(std::string cmd_name) {
    std::ostringstream stream;
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
    std::cout << stream.str() << "\n";
}

void outputRuby(std::string cmd_name) {
    std::ostringstream stream;
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
    std::cout << stream.str() << "\n";
}
void outputJava(std::string cmd_name) {
    std::ostringstream stream;
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
    std::cout << stream.str() << "\n";
}
void outputJS(std::string cmd_name) {
    std::ostringstream stream;
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
    std::cout << stream.str() << "\n";
}

void outputGo(std::string cmd_name) {
    std::ostringstream stream;
    stream << cmd_name << " := []uint8 {";
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
    stream << "};";
    std::cout << stream.str() << "\n";
}
