// Adapted from C++ Templates: The Complete Guide Second Edition example

#include<iostream>
#include<vector>


class UnderFlow {};

template<typename T>
class Stack {
public:
    Stack() = default;
    Stack(T type) : vec({type}) {}
    void push(const T &type) {
        vec.push_back(type);
    }
    T &top() {
        if(vec.size()==0)
            throw UnderFlow();
        return vec.back();
    }
    void pop() {
        if(vec.size()==0)
            throw UnderFlow();
        vec.pop_back();
    }
    void print() {
        std::cout << "Stack = { ";
        for(auto &i : vec) {
            std::cout << i << " ";
        }
        std::cout << "};\n";
    }
private:
    std::vector<T> vec;
};


int main() {
    try {
    	Stack value{100.5}; // deduce argument
    	Stack test_value = 500; // deduce argument
        value.print();
        
        for(int i = 0; i < 10; ++i)
            test_value.push(i);
        
        test_value.print();
        
    } catch(UnderFlow &e) {
        std::cerr << "Stack Underflow..\n";
    }
    return 0;
}
