#include"scan_symbol.hpp"

namespace scan {

    SymbolTable::SymbolTable() : index{0} {

    }

    void SymbolTable::enter(std::string name, std::string value) {
        data[name].name = name;
        data[name].value = value;
        if(data[name].index == -1)
            data[name].index = index++;
    }

    void SymbolTable::enter(std::string name, std::string value, int i) {
        data[name].name = name;
        data[name].value = value;
        if(data[name].index == -1)
            data[name].index = i;
    }


    void SymbolTable::enter(std::string name, double value) {
        data[name].name = name;
        data[name].val.fval = value;
        if(data[name].index == -1)
            data[name].index = index++;

    }
    void SymbolTable::enter(std::string name, long value) {
        data[name].name = name;
        data[name].val.lval = value;
        if(data[name].index == -1)
            data[name].index = index++;
    }

    void SymbolTable::enter_const(std::string text) {
        const_strings.push_back(text);
    }

    long &SymbolTable::getInteger(std::string name) {
        return data[name].val.lval;
    }
    double &SymbolTable::getDouble(std::string name) {
        return data[name].val.fval;
    }
    std::string &SymbolTable::getString(std::string name) {
        return data[name].value;
    }

    int SymbolTable::getIndex(std::string name) {
        return data[name].index;
    }

}