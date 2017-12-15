// Practice creating a tree.
// Than moving through the tree and solving the expression

#include<iostream>
#include<string>
#include<unordered_map>

struct Symbol {
    double value;
    std::string name;
};

enum class Var_type { EMPTY, DIGIT, VARIABLE, PLUS, EQUAL};

std::unordered_map<std::string, Symbol> symbols;

template<typename T>
class Node {
public:
    T token;
    double value;
    Var_type id;
    Node<T> *left, *right;
    Node() : id(Var_type::EMPTY), left(nullptr), right(nullptr) {}
    Node(const T &n_token, Var_type n_id, Node<T> *n_left, Node<T> *n_right) {
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
        root = new Node<T>("Root", Var_type::EMPTY, nullptr, nullptr);
    }
    ~Tree() {
        release(root);
    }
    
    void print() {
        printNodes(root);
    }
    
    double eval(Node<T> *node) {
        if(node == nullptr) return 0;
        std::cout << node->token << " current Node..\n";
        double v = 0;
    
        switch(node->id) {
            case Var_type::EQUAL: {
                v = eval(node->right);
                symbols[node->left->token].value = v;
                std::cout << node->left->token << " = " << v << "\n";
            }
                break;
            case Var_type::PLUS: {
                double op1 = eval(node->left);
                double op2 = eval(node->right);
                std::cout << op1 << "+" << op2 << "\n";
                return op1+op2;
            }
                break;
            case Var_type::VARIABLE:
                v = symbols[node->token].value;
                std::cout << "Var Value: " << v << "\n";
                break;
            case Var_type::DIGIT:
                v = node->value;
                std::cout << "Value: " << v << "\n";
                break;
            case Var_type::EMPTY:
                break;
        }
        return v;
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

void add_token(std::string name, double value) {
    symbols[name].name = name;
    symbols[name].value = value;
}

int main() {
    // add some leaves to the tree
    Tree<std::string> assign;
    Node<std::string> *node;
    assign.root->id = Var_type::EQUAL;
    assign.root->token = "=";
    assign.root->left = new Node<std::string>("x", Var_type::VARIABLE, nullptr, nullptr);
    assign.root->right = new Node<std::string>("+", Var_type::PLUS, nullptr, nullptr);
    Node<std::string> *plus = assign.root->right;
    node = assign.root->right;
    node->left = new Node<std::string>("10", Var_type::DIGIT, nullptr, nullptr);
    node->left->value = 10;
    node->right = new Node<std::string>("+", Var_type::PLUS, nullptr, nullptr);
    node = node->right;
    node->left = new Node<std::string>("x", Var_type::VARIABLE, nullptr, nullptr);
    node->right = new Node<std::string>("y", Var_type::VARIABLE, nullptr, nullptr);
    // print the leaves
    assign.print();
    // put some variables in symbol table
    add_token("x", 25);
    add_token("y", 50);
    // evaluate 
    double val = assign.eval(assign.root);
    std::cout << "value: " << val << "\n";
    return 0;
}
