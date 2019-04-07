#include<iostream>
#include<string>
#include<vector>
#include"filter.hpp"


template<typename T>
void procFilter(T &type) {
    type(/*frame*/);
}

int main() {
    std::vector<ac::FilterObject *> filter_stack;
    // Create new filter
    ac::SelfAlphaBlend blend;
    filter_stack.push_back(&blend);
    for(unsigned int i = 0; i < filter_stack.size(); ++i) {
        procFilter(*filter_stack[i]);
    }
    return 0;
}
