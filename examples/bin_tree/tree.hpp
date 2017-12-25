// Binary Tree Data Structure Class

#ifndef __TREE_B__H_
#define __TREE_B__H_

#include<iostream>
#include<string>
#define DEBUG_INFO

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
        Tree();
        ~Tree() {
            if(root != nullptr)
                cleanValues(root);
        }
        void addItem(const std::string &s_it, const T &item);
        bool getItem(T &tval, const std::string &s_it);
        T operator[](const std::string &s_it);
        void printValues();
    private:
        TreeNode<T> *root;
        void printValues(TreeNode<T> *node);
        void cleanValues(TreeNode<T> *node);
    };
    
    template<typename T>
    Tree<T>::Tree() : root(nullptr) {}
    
    template<typename T>
    void Tree<T>::addItem(const std::string &s_it, const T &item) {
        if(root == nullptr) {
            root = new TreeNode<T>();
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
            TreeNode<T> **values = &root, *current;
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
            *values = new TreeNode<T>();
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
        TreeNode<T> **values = &root, *current;
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
    T Tree<T>::operator[](const std::string &s_it) {
        T type;
        if(getItem(type, s_it))
            return type;
        
        throw KeyNotFound();
    }
    
    template<typename T>
    void Tree<T>::printValues() {
        printValues(root);
    }
    
    template<typename T>
    void Tree<T>::printValues(TreeNode<T> *node) {
        if(node != nullptr)
            std::cout << node->id << ":" << node->value << "\n";
        if(node != nullptr && node->left != nullptr)
            printValues(node->left);
        if(node != nullptr && node->right != nullptr)
            printValues(node->right);
    }
    
    template<typename T>
    void Tree<T>::cleanValues(TreeNode<T> *node) {
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
}

#endif

