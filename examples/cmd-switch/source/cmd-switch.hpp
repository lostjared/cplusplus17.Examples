#ifndef __CMDSWITCH_HPP__
#define __CMDSWITCH_HPP__
#include<iostream>
#include<string>
#include<vector>
namespace cmd {

    template<typename T>
    class ArgExcep {
    public:
        ArgExcep(const T &ww) : w{ww} {}
        T what() const { return w; }
    protected:
        T w;
    };

    template<typename T>
    class Token {
    public:
        T key,value;
    };

    class ArgumentList {
    public:
        ArgumentList(int argc, char **argv);
        bool check(std::string key);
        bool extract(std::string key, std::string &value);
        bool require(std::string key, std::string &value);
    protected:
        std::vector<Token<std::string>> items;
        
    };
}

#endif
