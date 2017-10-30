#include<iostream>
#include<sstream>
#include<string>
#include"linked.hpp"


int main() {
    util::LinkedList<std::string> lst;
    lst.add("Jared ");
    lst.add("Bruni");
    lst.PrintList();
    lst.remove(1);
    lst.PrintList();
    lst.remove(0);
    util::LinkedList<std::string> values;
    for(unsigned int i = 0; i < 15; ++i) {
        std::ostringstream stream;
        stream << "Value: " << i;
        values.add(stream.str());
    }
    int index = 0;
    // new if statement
    if(util::Node<std::string> *n = values.rootNode(); n != 0) {
        for(; n != 0; n = n->next) {
            std::cout << "At Index: " << index << " " << n->value << "\n";
            ++index;
        }
    }
    return 0;
}
