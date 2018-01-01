// Binary Tree Data Structure Class

#ifndef __TREE_B__H_
#define __TREE_B__H_

#include<iostream>
#include<string>

// comment out below line to not output debug information
//#define DEBUG_INFO

namespace tree {
    
    class KeyNotFound {};
    
    template<typename T>
    class TreeNode {
    public:
        T value;
        std::string id;
        TreeNode<T> *left, *right;
        TreeNode() : left(nullptr), right(nullptr), value(T()) { }
    };
    
    template<typename T>
    class Tree {
    public:
        using node_type = TreeNode<T>;
        using value_type = T;
        
        Tree();
        ~Tree() {
            if(owns == true && root != nullptr)
                cleanValues(root);
        }
        
        // move operations
        Tree(Tree<T> &&tr);
        Tree(Tree<T> &tr) = delete;
        Tree<T> &operator=(Tree<T> &&tr);
        Tree<T> &operator=(Tree<T> &t) = delete;
        
        void addItem(const std::string &s_it, const T &item);
        bool getItem(T &tval, const std::string &s_it);
        T &operator[](const std::string &s_it);
        node_type *findNode(std::string s_it);
        node_type *findCreate(std::string s_it);
        void printValues();
        void setScope(const std::string &s);
        std::string getScope();
        node_type *rootNode() { return root; }
        void setOwns(bool b);
        void moveTree(Tree<T> &&tr);
    private:
        node_type *root;
        void printValues(node_type *node);
        void cleanValues(node_type *node);
        std::string scope;
        bool owns;
    };
    
    template<typename T>
    Tree<T>::Tree() : root(nullptr), owns(true) {}
    
    template<typename T>
    void Tree<T>::moveTree(Tree<T> &&tr) {
        root = std::move(tr.root);
        scope = std::move(tr.scope);
        tr.setOwns(false);
        owns = true;
    }
    
    template<typename T>
    void Tree<T>::setOwns(bool b) {
        owns = b;
    }
    
    template<typename T>
    Tree<T>::Tree(Tree<T> &&tr) {
        moveTree(tr);
    }
    
    template<typename T>
    Tree<T> &Tree<T>::operator=(Tree<T> &&tr) {
        moveTree(tr);
    }
    
    template<typename T>
    void Tree<T>::addItem(const std::string &s_it, const T &item) {
        if(root == nullptr) {
            root = new node_type();
            if(!root) {
                std::cerr << "Error creating node..\n";
                return;
            }
            root->id = s_it;
            root->value = item;
            root->left = nullptr;
            root->right = nullptr;
#ifdef DEBUG_INFO
            std::cout << "added root: " << root->id << "\n";
#endif
            return;
        } else {
            node_type **values = &root, *current;
            while((current = *values) != nullptr) {
                if(current->id == s_it) {
                    current->value = item;
#ifdef DEBUG_INFO
                    std::cout << "Exisiting key found, updating: " << current->id <<":" << current->value << "\n";
#endif
                    return;
                }
                values = (current->id < s_it) ? &current->left : &current->right;
            }
            *values = new node_type();
            current = *values;
            if(!*values) {
                std::cerr << "Error could not allocate memory for tree node..\n";
                return;
            }
            current->id = s_it;
            current->value = item;
            current->left = current->right = nullptr;
#ifdef DEBUG_INFO
            std::cout << "Added: " << current->id << ":" << current->value << " to tree...\n";
#endif
        }
    }
    
    template<typename T>
    bool Tree<T>::getItem(T &tval, const std::string &s_it) {
        node_type **values = &root, *current;
        while((current = *values) != nullptr) {
            if(current->id == s_it) {
#ifdef DEBUG_INFO
                std::cout << "Exisiting key found:: " << current->id <<":" << current->value << "\n";
#endif
                tval = current->value;
                return true;
            }
            values = (current->id < s_it) ? &current->left : &current->right;
        }
        return false;
    }
    
    template<typename T>
    typename Tree<T>::node_type *Tree<T>::findNode(std::string s_it) {
        node_type **values = &root, *current;
        while((current = *values) != nullptr) {
            if(current->id == s_it) {
#ifdef DEBUG_INFO
                std::cout << "Exisiting key found:: " << current->id <<":" << current->value << "\n";
#endif
                return current;
            }
            values = (current->id < s_it) ? &current->left : &current->right;
        }
        return nullptr;
    }
    template<typename T>
    typename Tree<T>::node_type *Tree<T>::findCreate(std::string s_it)  {
        
        node_type **values = &root, *current;
        while((current = *values) != nullptr) {
            if(current->id == s_it) {
#ifdef DEBUG_INFO
                std::cout << "Exisiting key found:: " << current->id <<":" << current->value << "\n";
#endif
                return current;
            }
            values = (current->id < s_it) ? &current->left : &current->right;
        }
        *values = new node_type();
        current = *values;
        current->id = s_it;
        return current;
    }
    
    
    template<typename T>
    T &Tree<T>::operator[](const std::string &s_it) {
        node_type *cur = findNode(s_it);
        if(cur != nullptr) {
            return cur->value;
        }
        throw KeyNotFound();
    }
    
    template<typename T>
    void Tree<T>::printValues() {
        if(root != nullptr)
            printValues(root);
    }
    
    template<typename T>
    void Tree<T>::printValues(node_type *node) {
        if(node != nullptr)
            std::cout << "Node ID: " << node->id << " Node Value:" << node->value << "\n";
        if(node != nullptr && node->left != nullptr)
            printValues(node->left);
        if(node != nullptr && node->right != nullptr)
            printValues(node->right);
    }
    
    template<typename T>
    void Tree<T>::cleanValues(node_type *node) {
        if(node != nullptr && node->left != nullptr) {
#ifdef DEBUG_INFO
            std::cout << "release left: " << node->left->id << "\n";
#endif
            cleanValues(node->left);
        }
        if(node != nullptr && node->right != nullptr) {
#ifdef DEBUG_INFO
            std::cout << "release right: " << node->right->id << "\n";
#endif
            cleanValues(node->right);
        }
        
        if(node != nullptr) {
#ifdef DEBUG_INFO
            std::cout << "erasing: " << node->id << ":" << node->value << "\n";
#endif
            delete node;
        }
    }
    
    template<typename T>
    void Tree<T>::setScope(const std::string &s) {
        scope = s;
    }
    
    template<typename T>
    std::string Tree<T>::getScope() {
        return scope;
    }
}

#endif

