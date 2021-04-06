// use on the shell with pipe
// example
// cat text-file.txt | ./replace-test --repalce="string" --with="replacement"

#include<iostream>
#include<string>
#include"cmd-switch.hpp"

std::string replace_string(std::string orig, std::string with, std::string rep) {
    auto pos = orig.find(with);
    if(pos == std::string::npos) {
        return orig;
    }
    std::string left;
    left = orig.substr(0, pos);
    std::string right;
    right = orig.substr(pos+with.length(), orig.length());

    std::string f;
    f = left+rep+right;
    return replace_string(f,with,rep);
}

int main(int argc, char **argv) {
    try {
        
        std::string rp;
        std::string re;
        cmd::ArgumentList<std::string> argz(argc, argv);
        argz.require("--replace", rp, "replace string");
        argz.require("--with", re, "replace with");
        
        while(!std::cin.eof()) {
            std::string s;
            std::getline(std::cin, s);
            std::string output;
            output = replace_string(s, rp, re);
            std::cout << output << "\n";
        }
    }
    catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
