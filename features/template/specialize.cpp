/*
 Practice for writing template specialization
 doesn't do much, but the code itself is whats important
 just for remembering all this stuff
 
 */
#include<iostream>
#include<string>
#include<cstdlib>
#include<sstream>

constexpr int SIZE_X=4;

template<typename T, int size_x, int size_y>
class Mult {
public:
    T array[size_x][size_y];
    void print() {
        std::cout << "Generic...\n";
        for(unsigned int i = 0; i < size_x; ++i) {
            for(unsigned int z = 0; z < size_y; ++z) {
                std::cout << "array[" << i << ", " << z << "] = " << array[i][z] << ";\n";
            }
        }
    }
    unsigned int width() const { return size_x; }
    unsigned int height() const { return size_y; }
};

template<int size_x, int size_y>
class Mult<std::string, size_x, size_y> {
public:
    std::string array[size_x][size_y];
    void print() {
        std::cout << "String specialization\n";
        for(unsigned int i = 0; i < size_x; ++i) {
            std::cout << "{\n";
            for(unsigned int z = 0; z < size_y; ++z) {
                std::cout << array[i][z] << " ";
            }
            std::cout << "\n}\n";
        }
    }
    unsigned int width() const { return size_x; }
    unsigned int height() const { return size_y; }
};

template<typename T>
void echo(T &type) {
    std::cout << "Printing type....\n";
    type.print();
}

template<typename T, int size_x, int size_y>
void PrintMult(Mult<T, size_x, size_y> &m) {
    std::cout << "Echo generic type..\n";
    m.print();
}

template<>
void PrintMult<std::string, SIZE_X, SIZE_X>(Mult<std::string, SIZE_X, SIZE_X> &m) {
    std::cout << "Echo string type..\n";
    m.print();
}

int main() {

    Mult<int, SIZE_X, SIZE_X> m1;
    for(unsigned int i = 0; i < m1.width(); ++i) {
        for(unsigned int z = 0; z < m1.height(); ++z) {
            m1.array[i][z] = rand()%10;
        }
    }
    echo(m1);
    Mult<std::string, SIZE_X, SIZE_X> m2;
    for(unsigned int i = 0; i < m2.width(); ++i) {
        for(unsigned int z = 0; z < m2.height(); ++z) {
            std::ostringstream stream;
            stream << "Value is: " << rand()%10;
            m2.array[i][z] = stream.str();
        }
    }
    echo(m2);
    PrintMult(m1);
    PrintMult(m2);
    
    return 0;
}
