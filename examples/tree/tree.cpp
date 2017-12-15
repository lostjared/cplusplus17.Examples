// Practice creating a tree.

#include<iostream>
#include<string>

template<typename T>
class Node {
public:
    T token;
    unsigned int id;
    Node *left, *right;
    Node() : id(0), left(nullptr), right(nullptr) {}
    Node(const T &n_token, unsigned int n_id, Node *n_left, Node *n_right) {
        token = n_token;
        id = n_id;
        left = n_left;
        right = n_right;
    }
};

template<typename T>
class Tree {
public:
    Tree() {
        root = new Node<T>("Root", 0, nullptr, nullptr);
    }
    ~Tree() {
        release(root);
    }
    Node<T> *root;
    
    void printNodes(Node<T> *n) {
        
        if(n != 0)
            std::cout << "Node: " << n->token << ":" << n->id << "\n";
        
        if(n->left != 0)
            printNodes(n->left);
        
        if(n->right != 0)
            printNodes(n->right);
        
    }
    
    void print() {
        printNodes(root);
    }
    
    void release(Node<T> *n) {
        if(n->left != 0)
            release(n->left);
        if(n->right != 0)
            release(n->right);
        if(n != 0)
            delete n;
    }
};


int main() {
    Tree<std::string> data;
    data.root->left = new Node<std::string>("Hello ", 1, new Node<std::string>(" World", 2, nullptr, nullptr), new Node<std::string>(" Tree!", 3, nullptr, nullptr));
    data.print();
    return 0;
}
