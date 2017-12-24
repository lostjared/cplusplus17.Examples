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
            cleanValues(root);
        }
        void addItem(const std::string &s_it, const T &item);
        bool getItem(T &tval, const std::string &s_it);
        T &operator[](const std::string &s_it);
        void printValues();
    private:
        TreeNode<T> *root;
        void printValues(TreeNode<T> *root);
        void cleanValues(TreeNode<T> *root);
    };

    template<typename T>
    Tree<T>::Tree() : root(nullptr) {
        
    }
    
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
        //TreeNode<T>
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
    T &Tree<T>::operator[](const std::string &s_it) {
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
    void Tree<T>::printValues(TreeNode<T> *root) {
        if(root != nullptr)
            std::cout << root->id << ":" << root->value << "\n";
        if(root != nullptr && root->left != nullptr)
            printValues(root->left);
        if(root != nullptr && root->right != nullptr)
            printValues(root->right);;
    }
    
    template<typename T>
    void Tree<T>::cleanValues(TreeNode<T> *root) {
        if(root != nullptr && root->left != nullptr)
            cleanValues(root->left);
        if(root != nullptr && root->right != nullptr)
            cleanValues(root->right);
        
        if(root != nullptr) {
#ifdef DEBUG_INFO
            std::cout << "erasing: " << root->id << ":" << root->value << "\n";
#endif
            delete root;
        }
    }

    
}

#endif

