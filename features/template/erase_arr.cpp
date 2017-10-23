#include<iostream>
#include<string>


template<typename T>
void erase_array(T **type, unsigned long size) {
    for(unsigned long i = 0; i < size; ++i)
        delete [] type[i];
    
    delete [] type;
}

template<typename T>
T **new_dim(unsigned long x, unsigned long y) {
    T **type = new T*[x];
    for(unsigned long i = 0; i < x; ++i) {
        type[i] = new T[y];
    }
    return type;
}

int main() {
    std::cout << "Filling array...\n";
    unsigned long size_x = 10;
    char **array_ = new_dim<char>(size_x, 100);
    // fill with junk
    for(unsigned i = 0; i < 10; ++i) {
        sprintf(array_[i], "%s", "Hello World!");
        std::cout << array_[i] << "\n";
    }
    erase_array<char>(array_, 10);
    std::cout << "Erased...\n";
    return 0;
}
