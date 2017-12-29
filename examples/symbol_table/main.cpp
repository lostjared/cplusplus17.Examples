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
    
    symbols.pushTree();
    symbols.insertTop("Local", SymbolType("Local", 100));
    symbols.insertGlobal("Global", SymbolType("Global", 100));
    
    symbols.printTable();
    
    return 0;
}
