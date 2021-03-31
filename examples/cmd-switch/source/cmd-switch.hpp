#ifndef __CMDSWITCH_HPP__
#define __CMDSWITCH_HPP__
#include<iostream>
#include<string>
#include<vector>
namespace cmd {

    class ArgExcep {
    public:
        ArgExcep(const std::string &ww) : w{ww} {}
        std::string what() const { return w; }
    protected:
        std::string w;
    };

    class Token {
    public:
        std::string key,value;
    };

    class ArgumentList {
    public:
        ArgumentList(int argc, char **argv);
        bool check(std::string key);
        bool extract(std::string key, std::string &value);
    protected:
        std::vector<Token> items;
        
    };
}

#endif
