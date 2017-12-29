#ifndef __TABLE__H_
#define __TABLE__H_


#include<iostream>
#include<string>
#include<vector>
#include"tree.hpp"

namespace sym {
    template<typename T>
    class SymbolTable {
    public:
        SymbolTable();
        bool exisits(std::string n);
        void pushTree();
        void popTree();
        void insertTop(std::string n, const T &type);
        void insertGlobal(std::string n, const T &type);
        typename tree::Tree<T>::node_type *searchStack(std::string n);
        
    private:
        std::vector<tree::Tree<T>> tree_stack;
    };
    
    template<typename T>
    SymbolTable<T>::SymbolTable() {
        tree_stack.push_back(tree::Tree<T>());
    }
    
    template<typename T>
    void SymbolTable<T>::pushTree() {
        tree_stack.push_back(tree::Tree<T>());
    }
    
    template<typename T>
    void SymbolTable<T>::popTree() {
        tree_stack.pop_back();
    }
    
	template<typename T>
    bool SymbolTable<T>::exisits(std::string n) {
        for(int i = tree_stack.size()-1; i > 0; --i) {
            typename tree::Tree<T>::node_type *node;
            node = tree_stack[i].findNode(n);
            if(node != nullptr) return true;
        }
        return false;
    }
    
    template<typename T>
    typename tree::Tree<T>::node_type *SymbolTable<T>::searchStack(std::string n) {
        for(int i = tree_stack.size()-1; i > 0; --i) {
            typename tree::Tree<T>::node_type *node;
            node = tree_stack[i].findNode(n);
            if(node != nullptr) return node;
        }
        return nullptr;
    }
    
    template<typename T>
    void SymbolTable<T>::insertTop(std::string n, const T &type) {
        int top_level = tree_stack.size()-1;
        tree_stack[top_level].addItem(n, type);
    }
    
    template<typename T>
    void SymbolTable<T>::insertGlobal(std::string n, const T &type) {
        if(tree_stack.size()>0)
            tree_stack[0].addItem(n, type);
    }
}


#endif

