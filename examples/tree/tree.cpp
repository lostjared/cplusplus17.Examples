// Practice creating a tree.

#include<iostream>
#include<string>

template<typename T>
class Node {
public:
    T token;
    unsigned int id;
    Node<T> *left, *right;
    Node() : id(0), left(nullptr), right(nullptr) {}
    Node(const T &n_token, unsigned int n_id, Node<T> *n_left, Node<T> *n_right) {
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
            std::cout << "Node: " << n->token << ":" << static_cast<char>(n->id) << "\n";
        
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
        if(n != 0) {
            std::cout << "releasing: " << n->token << "\n";
            delete n;
        }
    }
};


int main() {
    Tree<std::string> data;
    data.root->left = new Node<std::string>("Hello ", 's', new Node<std::string>(" World", 's', nullptr, nullptr), new Node<std::string>(" Tree!", 's', nullptr, nullptr));
    data.print();
    Tree<std::string> assign;
    Node<std::string> *node;
    assign.root->id = '=';
    assign.root->left = new Node<std::string>("x", 'v', nullptr, nullptr);
    assign.root->right = new Node<std::string>("10", 'n', nullptr, nullptr);
    node = assign.root->right;
    node->id = '+';
    node->left = new Node<std::string>("x", 'v', nullptr, nullptr);
    node->right = new Node<std::string>("y", 'v', nullptr, nullptr);
    assign.print();
    return 0;
}
