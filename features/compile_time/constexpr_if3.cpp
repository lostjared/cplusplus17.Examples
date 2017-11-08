#include<iostream>
#include<type_traits>


template<typename T>
void PrintValue(const T &type) {
    if constexpr(std::is_same<T, int>::value) {
        std::cout << "Genreated for integer type..\n";
        return;
    }
    else if constexpr(std::is_same<T, long>::value) {
        std::cout << "Genreated for long...\n";
        return;
    }
    else if constexpr(std::is_same<T, std::string>::value) {
        std::cout << "String class...\n";
        return;
    } else {
        std::cout << "Type not tested for...\n";
    }
}

int main() {
    PrintValue(100);
    PrintValue(long(100000));
    PrintValue(std::string("test"));
    PrintValue(100u);
    return 0;
}
