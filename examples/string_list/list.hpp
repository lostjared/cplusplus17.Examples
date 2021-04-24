// trying to practice
#ifndef _STRING_LIST_H_
#define _STRING_LIST_H_

#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>

namespace lst {


    class SList {
    public:
        SList(std::string fname) : fname_{fname} {
            std::fstream file;
            file.open(fname, std::ios::in);
            if(!file.is_open()) {
                return;
            }
            while(!file.eof()) {
                std::string s;
                std::getline(file, s);
                if(file) {
                    auto pos = s.find(":");
                    std::string left=s.substr(0, pos);
                    std::string right=s.substr(pos+1, s.length());
                    values[left] = right;
                }
            }
            file.close();
        }
        ~SList() {
            std::fstream file;
            file.open(fname_, std::ios::out);
            if(!file.is_open()) return;
            for(auto i = values.begin(); i != values.end(); ++i) {
                file << i->first << ":" << i->second << "\n";
            }
            file.close();
        }
        
        void set(std::string name, std::string value) {
            values[name] = value;
        }
        std::string get(std::string value) {
            return values[value];
        }
        
        
        void print() {
            for(auto i = values.begin(); i != values.end(); ++i) {
                std::cout << i->first << ":" << i->second << "\n";
            }
        }
        
    protected:
        std::unordered_map<std::string, std::string> values;
        std::string fname_;
    };
}

#endif

