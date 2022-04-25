#ifndef _SCAN_SYMBOL_H_
#define _SCAN_SYMBOL_H_

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>

namespace scan {

    class Scanner;

    struct Variable {
        Variable() = default;
        std::string name, value;
        union {
            double fval;
            long lval;
        } val;
        int index = -1;
        bool id = false;

        void copy(const Variable &v) {
            name = v.name;
            value = v.value;
            val = v.val;
            index = v.index;
            id = v.id;
        }

        Variable(const Variable &v) {
            copy(v);
        }

        Variable(Variable &&v) {
            copy(v);
        }

        Variable &operator=(const Variable &v) {
            copy(v);
            return *this;
        }

        Variable &operator=(Variable &&v) {
            copy(v);
            return *this;
        }

        Variable(double d) {
            val.fval = d;
        }
        Variable(std::string s) : value{s} {
            val.fval = 0;
        }
    };

    std::ostream &operator<<(std::ostream &out, const Variable &v);

    class SymbolTable {
    public:
        SymbolTable();
        void enter_id(std::string name);
        void enter(std::string name, std::string value);
        void enter(std::string name, std::string value, int index);
        void enter(std::string name, double value);
        void enter(std::string name, long value);
        bool valid(std::string name);
        void enter_const(std::string text);
        long &getInteger(std::string name);
        double &getDouble(std::string name);
        std::string &getString(std::string name);
        int getIndex(std::string name);
        friend class Scanner;
        friend void crunch(Scanner *scan, std::ostream &out);
        SymbolTable *parent = nullptr;
        std::string name = "global";
        void print();
    protected:
        std::unordered_map<std::string, Variable> data;
        std::vector<std::string> const_strings;
        int index;

    };
}



#endif