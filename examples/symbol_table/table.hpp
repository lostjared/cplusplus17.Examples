#ifndef __TABLE__H_
#define __TABLE__H_


#include<iostream>
#include<string>
#include"tree.hpp"

namespace sym {
    template<typename T>
    class SymbolTable {
        
    private:
        tree::Tree<T> tree;
    };
}

#endif

