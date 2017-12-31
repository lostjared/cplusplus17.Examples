/*
 Try out using the Symbol Table with some tests...
 */

#include "table.hpp"

struct SymbolType {
    std::string name;
    double value;
    SymbolType() : value(0) {}
    SymbolType(std::string n, double v) : name(n), value(v) {}
};

std::ostream &operator<<(std::ostream &out, SymbolType &type) {
    out << type.name << ":" << type.value << "\n";
    return out;
}

int main() {
    
    sym::SymbolTable<SymbolType> symbols;
    
    symbols.pushTree("Local[main]");
    symbols.insertTop("Local_Var", SymbolType("Local", 255));
    symbols.insertGlobal("Global_Var", SymbolType("Global", 1024));
    symbols.insertTop("x", SymbolType("x", 1));
    symbols.insertGlobal("x", SymbolType("x", 100));
    
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
    
    symbols.printTable();
    
    return 0;
}
