#include<iostream>
#include"linked.hpp"

int main() {
    util::LinkedList<std::string> lst;
    lst.add("Jared ");
    lst.add("Bruni");
    lst.PrintList(lst.rootNode());
    lst.remove(1);
    lst.PrintList(lst.rootNode());
    return 0;
}
