#include<iostream>

[[nodiscard]] int *gen();

int main() {
    
    int *x = gen();
    int *y = gen();
    
    delete [] x;
    delete [] y;
    
    return 0;
}

[[nodiscard]] int *gen() {
    
    return new int[25];
}
