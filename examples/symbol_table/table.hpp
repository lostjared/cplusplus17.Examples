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
        void insertLevel(int level, std::string n, const T &type);
        void insertTop(std::string n, const T &type);
        void insertGlobal(std::string n, const T &type);
        typename tree::Tree<T>::node_type *searchStack(std::string n);
        void printTable();
        tree::Tree<T> *getTree(int index);
        size_t size() const { return tree_stack.size(); }
        
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
        for(int i = tree_stack.size()-1; i >= 0; --i) {
            typename tree::Tree<T>::node_type *node;
            node = tree_stack[i].findNode(n);
            if(node != nullptr) return true;
        }
        return false;
    }
    
    template<typename T>
    typename tree::Tree<T>::node_type *SymbolTable<T>::searchStack(std::string n) {
        for(int i = tree_stack.size()-1; i >= 0; --i) {
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

    template<typename T>
    void SymbolTable<T>::insertLevel(int level, std::string n, const T &type) {
        if(level >= 0 && level < tree_stack.size()) {
            tree_stack[level].addItem(n, type);
        }
    }

    template<typename T>
    void SymbolTable<T>::printTable() {
        std::cout << "Symbol Table output..\n";
        for(int i = tree_stack.size()-1; i >= 0; --i) {
            if(i == 0) std::cout <<  "*** Global Table ***\n";
            else std::cout << "*** Local Level: " << i << "***\n";
            tree_stack[i].printValues();
        }
    }

    template<typename T>
    tree::Tree<T> *SymbolTable<T>::getTree(int index) {
        if(index >= 0 && index < tree_stack.size())
            return &tree_stack[index];
        return nullptr;
    }

}


#endif

