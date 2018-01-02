/*
 Try out using the Symbol Table with some tests...
 */
// comment out below line for no debug info
//#define DEBUG_INFO
#include "table.hpp"
#include<algorithm>

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
    std::string name, value;
    std::cout << "Enter some symbols use quit as name to stop loop\n";
    do {
        std::cout << "Enter symbol name: ";
        std::getline(std::cin, name);
        if(name != "quit") {
            std::cout << "Enter symbol value: ";
        	std::getline(std::cin, value);
            symbols.insertTop(name, SymbolType(name, value));
            symbols.printTable();
        }
    } while(name != "quit");
    symbols.pushTree("main_func");
    symbols.insertTop("Test 1 2 3", SymbolType("Test 1 2 3", "Value"));
    symbols.pushTree("local");
    symbols.insertTop("local-if", SymbolType("local-if", "Val"));
    symbols.printTable();
    symbols.popTree();
    symbols.popTree();
    return 0;
}
