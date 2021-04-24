#include "list.hpp"

int main(int argc, char **argv) {
    lst::SList lst("test.txt");
    std::cout << "enter value:";
    std::string val1, val2;
    std::cin >> val1 >> val2;
    lst.set(val1, val2);
    lst.print();
    return 0;
    
}
