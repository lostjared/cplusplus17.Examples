#ifndef _SCAN_SYMBOL_H_
#define _SCAN_SYMBOL_H_

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>

namespace scan {

    class Scanner;

    struct Variable {
        std::string name, value;
        union {
            double fval;
            long lval;
        } val;
        int index = 0;
    };

    class SymbolTable {
    public:
        SymbolTable();
        void enter(std::string name, std::string value);
        void enter(std::string name, double value);
        void enter(std::string name, long value);
        void enter_const(std::string text);
        long &getInteger(std::string name);
        double &getDouble(std::string name);
        std::string &getString(std::string name);
        int getIndex(std::string name);
        friend class Scanner;
        std::unordered_map<std::string, Variable> data;
        std::vector<std::string> const_strings;
        int index;

        friend void crunch(Scanner *scan, std::ostream &out);
    };
}



#endif