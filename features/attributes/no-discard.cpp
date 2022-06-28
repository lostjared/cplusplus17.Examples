#include<iostream>

[[nodiscard]] int *gen();

int main() {
    
    int *x = gen();
    gen(); /// should warn return discarded.
    
    delete [] x;
    
    return 0;
}

[[nodiscard]] int *gen() {
    
    return new int[25];
}
