#include<iostream>
#include<string>
#include<vector>
#include"filter.hpp"



void procFilter(ac::FilterObject *obj) {
    (*obj)(/*mat*/);
}

int main() {
    std::vector<ac::FilterObject *> filter_stack;
    // Create new filter
    ac::SelfAlphaBlend blend;
    filter_stack.push_back(&blend);
    ac::SelfScale scale;
    filter_stack.push_back(&scale);
    for(unsigned int i = 0; i < filter_stack.size(); ++i) {
        procFilter(filter_stack[i]);
    }
    return 0;
}

