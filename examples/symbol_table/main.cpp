#include "table.hpp"

struct SymbolType {
    std::string name;
    double value;
};

std::ostream &operator<<(std::ostream &out, SymbolType &type) {
    out << type.name << ":" << type.value << "\n";
    return out;
}

int main() {
    
    sym::SymbolTable<SymbolType> symbols;
    
    
    return 0;
}
