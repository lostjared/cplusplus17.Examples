/*
 	Simple Linked List example with Templates
 	Just trying some stuff out, not meant to be used.
*/


#ifndef __LINKED__LIST_H__
#define __LINKED__LIST_H__

#include<iostream>
#include<string>

namespace util {
    
    template<typename T>
    class Node {
    public:
        T value;
        Node<T> *next;
        
        Node() {
            next = nullptr;
            value = T();
        }
        
        Node(const T &type) {
            value = type;
            next = nullptr;
        }
    };
    
    template<typename T>
    class LinkedList {
    public:
        LinkedList() = default;
        LinkedList(const LinkedList<T> &type) = delete;
        LinkedList(LinkedList<T> &&r) = delete;
        LinkedList<T> &operator=(const LinkedList<T> &type) = delete;
        LinkedList<T> &operator=(LinkedList<T> &&r) = delete;
        
        ~LinkedList() {
            release();
        }
        
        Node<T> *add(const T &type) {
            Node<T> *i = &root;
            while(i->next != nullptr) {
                i = i->next;
            }
            i->next = new Node<T>(type);
            return i->next;
        }
        

        bool remove(int index) {
            if(index == 0) {
                Node<T> *node;
                node = root.next;
                if(root.next != nullptr) {
                    node = root.next;
                    if(node->next != nullptr) {
                        root.next = node->next;
                        std::cout << "Removed: " << node->value << "\n";
                        delete node;
                        return true;
                    } else {
                        std::cout << "Removed: " << node->value << "\n";
                        delete node;
                        root.next = nullptr;
                        return true;
                    }
                }
            }
            int count = 0;
            Node<T> *n, *prev;
            Node<T> **lst = &root.next;
            prev = root.next;
            while((n = *lst) != nullptr) {
                if(count == index) {
                    if(prev != nullptr) {
                        prev->next = n->next;
                        std::cout << "Removed: " << n->value << "\n";
                        delete n;
                        return true;
                    }
                }
                prev = n;
                lst = &n->next;
                ++count;
            }
            return false;
        }
        
        bool empty() const {
            return (root.next == nullptr) ? true : false;
        }
        
        Node<T> *rootNode() { return root.next; }
        
        void PrintList(Node<T> *n) {
            if(n != nullptr)
                std::cout << "Item: " << n->value << "\n";
            if(n->next != nullptr)
                PrintList(n->next);
        }
        
        void PrintList() {
            PrintList(rootNode());
        }
        
    private:
        Node<T> root;
        
        void release(Node<T> *n) {
            if(n->next != nullptr)
                release(n->next);
            
            if(n != nullptr) {
                std::cout << "Deleted: " << n->value << "\n";
                delete n;
                n = nullptr;
            }
        }
        
        void release() {
            if(rootNode() != nullptr)
            	release(rootNode());
        }

    };
    
}

#endif


