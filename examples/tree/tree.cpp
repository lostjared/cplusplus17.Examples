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
    Node<T> *root;
    
    Tree() {
        root = new Node<T>("Root", 0, nullptr, nullptr);
    }
    ~Tree() {
        release(root);
    }
    
    void print() {
        printNodes(root);
    }
    
private:
    void printNodes(Node<T> *n) {
        
        if(n != nullptr)
            std::cout << "Node: " << n->token << ":" << n->id << "\n";
        
        if(n->left != nullptr)
            printNodes(n->left);
        
        if(n->right != nullptr)
            printNodes(n->right);
        
    }
    
    void release(Node<T> *n) {
        if(n->left != nullptr)
            release(n->left);
        if(n->right != nullptr)
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
