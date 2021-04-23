// trying to write something to practice
#ifndef __HPP_HPP__
#define __HPP_HPP__

#include<iostream>
#include<string>

class ErrorUnder{};
class ErrorOver{};

template<typename T>
class Stack {
public:
    Stack(int Size);
    ~Stack();
    void push(const T &type);
    T pop();
    size_t size() const { return size_of; }
    void printItems() const;
protected:
    T *type;
    size_t size_of;
    size_t index;
};

template<typename T>
Stack<T>::Stack(int Size) {
    type = new T[Size+1];
    size_of = Size;
    index = 0;
}

template<typename T>
Stack<T>::~Stack() {
    delete [] type;
    type = nullptr;
}

template<typename T>
void Stack<T>::push(const T &t) {
    if(index+1 < size_of)
    type[index++] = t;
    else
        throw ErrorOver();
}

template<typename T>

T Stack<T>::pop() {
    if(index-1 > 0) {
    T t;
    t = type[index--];
    return t;
    }
    else {
        throw ErrorUnder();
    }
}

template<typename T>
void Stack<T>::printItems() const {
    for(int i = 0; i < index; ++i) {
        std::cout << type[i] << "\n";
    }
}

#endif
