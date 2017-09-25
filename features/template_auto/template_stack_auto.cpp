#include<iostream>
#include<array>


class Exception{};

template<typename T, auto S>
class Stack {
public:
    using size_type = decltype(S);
    Stack();
    void push(const T &type);
    void pop();
    T top();
    size_type length();
    size_type size;
private:
    std::array<T, S> values;
};

template<typename T, auto S>
Stack<T,S>::Stack() : size(0) {
    
}

template<typename T, auto S>
void Stack<T,S>::push(const T &type) {
    values[size] = type;
    ++size;
}

template<typename T, auto S>
void Stack<T,S>::pop() {
    if(size <= 0)
        throw Exception();
    --size;
}

template<typename T, auto S>
T Stack<T,S>::top() {
    if(size <= 0)
        throw Exception();
    return values[size-1];
}

template<typename T, auto S>
typename Stack<T,S>::size_type Stack<T, S>::length() {
    return S;
}


int main() {
    
    try {
        Stack<int, 255> int_stack;
        Stack<unsigned int, 1024u> uint_stack;
        for(unsigned int i = 0; i < 255; ++i) {
            std::cout << "int: push " << i << "\n";
            int_stack.push(i);
            std::cout << "uint: push " << i << "\n";
            uint_stack.push(i);
        }
        for(unsigned int q = 0; q < 120; ++q) {
            std::cout << "top int: " << int_stack.top() << "/" << int_stack.length() << "\n";
            std::cout << "top uint: " << uint_stack.top() << "/" << uint_stack.length() << "\n";
            int_stack.pop();
            uint_stack.pop();
        }
    } catch(Exception) {
        
    }
    
    return 0;
}
