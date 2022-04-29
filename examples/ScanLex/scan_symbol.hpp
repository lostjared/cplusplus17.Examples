#ifndef _SCAN_SYMBOL_H_
#define _SCAN_SYMBOL_H_

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>

namespace scan {

    class Scanner;


    enum VAR_TYPE { VAR_CONST, VAR_VAR, VAR_FUNC_NAME, VAR_EMPTY };
    enum VAR_TYPE_INFO { VAR_DOUBLE, VAR_STRING, VAR_ID, VAR_ARRAY };
    static const char *vtype_info[] = {"Numeric", "String", "Identifier", "Array", 0 };

    struct Variable {
        Variable() = default;
        std::string name, value;
        union {
            double fval;
            long lval;
        } val;
        int index = -1;
        VAR_TYPE type = VAR_EMPTY;
        bool id = false;
        VAR_TYPE_INFO type_info;
        void copy(const Variable &v);
        Variable(const Variable &v);
        Variable(Variable &&v);
        Variable &operator=(const Variable &v);
        Variable &operator=(Variable &&v);
        Variable(double d) ;
        Variable(const std::string &s);
        Variable(const std::string &n, const std::string &v);
        Variable(const std::string &n, VAR_TYPE_INFO t);
        Variable(const std::string &n, VAR_TYPE t, VAR_TYPE_INFO vt);
        Variable(const std::string &n, const double &d);
    };

    std::ostream &operator<<(std::ostream &out, const Variable &v);
    std::ostream &operator<<(std::ostream &out, const VAR_TYPE_INFO &v);

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
        Variable &getVar(const std::string &name);
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