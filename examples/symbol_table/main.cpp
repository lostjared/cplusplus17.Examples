/*
 Try out using the Symbol Table with some tests...
 */
// comment out below line for no debug info
//#define DEBUG_INFO
#include "table.hpp"

struct SymbolType {
    std::string name, str_val;
    double value;
    SymbolType() : value(0) {}
    SymbolType(std::string n, double v) : name(n), value(v) {}
    SymbolType(std::string n, std::string v) : name(n), str_val(v), value(0) {}
};

std::ostream &operator<<(std::ostream &out, SymbolType &type) {
    out << type.name << ":" << type.value << ":" << type.str_val;
    return out;
}

template<typename T>
void outputTable(sym::SymbolTable<T> &type) {
    for(auto i = type->rbegin(); i != type->rend(); ++i) {
        auto v = i->get();
        v->printValues();
    }
}

int main() {
    sym::SymbolTable<SymbolType> symbols;
    symbols.pushTree("Local[main]");
    symbols.insertTop("x", SymbolType("test", 25));
    typename tree::Tree<SymbolType>::node_type *var = symbols.searchStack("x");
    if(var != nullptr) {
        std::cout << "Found symbol: " << var->value << "\n";
    } else {
        std::cout << "Symbol Not Found\n";
    }
    var = symbols.searchStack("Local_Var");
    if(var != nullptr) {
        std::cout << "Found symbol: " << var->value << "\n";
    } else {
        std::cout << "Symbol Not Found\n";
    }
    for(int i = 0;  i < 10; ++i) {
        symbols.pushTree();
        symbols.insertTop("test1", SymbolType("test1", i));
        symbols.printTable();
        symbols.popTree();
    }
    // test move constructor
    sym::SymbolTable<SymbolType> move_sym(std::move(symbols));
    // output with iterator
    outputTable<SymbolType>(move_sym);
    return 0;
}
