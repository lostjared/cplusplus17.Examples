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

    // template so you can subclass string if you want
    template<typename T>
    class ArgumentList {
    public:
        ArgumentList(int argc, char **argv);
        bool check(T key);
        bool check_require(T key);
        bool extract(T key, T &value);
        bool require(T key, T &value, T desc);
        void print();
        Token<T> &item(unsigned int index) { return items[index]; }
        unsigned int size() const { return items.size(); }
    protected:
        std::vector<Token<T>> items;
        
    };

    class ArgumentStringList {
    public:
        ArgumentStringList(int argc, char **argv);
        ArgumentList<std::string> argz;
    };

    bool Argument_FindInList(std::vector<std::string> &lst, ArgumentStringList &alst);

    template<typename T>
    ArgumentList<T>::ArgumentList(int argc, char **argv) {
        for(int i = 1; i < argc; ++i) {
            T s{argv[i]};
            auto pos = s.find("=");
            if(pos != std::string::npos) {
                T left = s.substr(0, pos);
                T right = s.substr(pos+1, s.length());
                if(right.length() == 0)
                    throw ArgExcep<T>("Argument Error: Zero Length");
                
                Token<T> token;
                token.key = left;
                token.value = right;
                items.push_back(token);
            } else {
                Token<T> token;
                token.key = "$";
                token.value = argv[i];
                items.push_back(token);
            }
        }
    }
    template<typename T>
    bool ArgumentList<T>::check(T key) {
        for(int i = 0; i < items.size(); ++i) {
            if(items[i].key == "$") {
                if(items[i].value == key) {
                    return true;
                }
            }
        }
        return false;
    }

    template<typename T>
    bool ArgumentList<T>::check_require(T key) {
        for(int i = 0; i < items.size(); ++i) {
            if(items[i].key == "$") {
                if(items[i].value == key) {
                    return true;
                }
            }
        }
        throw ArgExcep<T>("Argument Error: " + key + " required");
        return false;
    }

    template<typename T>
    bool ArgumentList<T>::extract(T key, T &value) {
        for(int i = 0; i < items.size(); ++i) {
            if(items[i].key == "$" && items[i].value == key) {
                return false;
            }
            if(items[i].key == key) {
                value = items[i].value;
                return true;
            }
        }
        return false;
    }

    template<typename T>
    bool ArgumentList<T>::require(T key, T &value, T desc) {
        for(int i = 0; i < items.size(); ++i) {
            
            if(items[i].key == "$" && items[i].value == key) {
                throw ArgExcep<T>("Argument Error: " + key + " required argument missing value...");
                return false;
            }
            
            if(items[i].key == key) {
                value = items[i].value;
                return true;
            }
        }
        throw ArgExcep<T>("Argument Error: " + key + " Required [" + desc + "]");
        return false;
    }


    template<typename T>
    void ArgumentList<T>::print() {
        for(int i = 0; i < items.size(); ++i) {
            if(items[i].key == "$")
                std::cout << items[i].value << "\n";
            else
                std::cout << items[i].key << ":" << items[i].value << "\n";
        }
    }

}

#endif
