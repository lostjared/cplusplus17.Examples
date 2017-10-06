/*
 
 C++17
 
 Testing casting inbetween certain types
 using templates and reinterpret_cast
 
*/


#include<iostream>

template<typename T, auto S>
class ArrayCast {
public:
    using size_type = decltype(S);
    ArrayCast() = default;
    T &operator[](unsigned int index) {
        return arr[index];
    }
    T *all() { return &arr[0]; }
    unsigned char *bytes() { return reinterpret_cast<unsigned char*>(&arr[0]); }
    unsigned int size_bytes() { return sizeof(arr); }
    // cast with compile time check to ensure same size
    template<typename T2>
    T2 *cast() {
        static_assert(sizeof(T2)==(sizeof(T)*S), "Wrong size");
        return reinterpret_cast<T2*>(arr);
    }
    size_type array_size() const { return S; }
private:
    T arr[S];
};


int main() {
    ArrayCast<unsigned char, 4u> ac;
    ac[0] = 255;
    ac[1] = 255;
    ac[2] = 255;
    ac[3] = 255;
    unsigned int *type = ac.cast<unsigned int>();
    //unsigned long *long_type = ac.cast<unsigned long>(); // will cause an error because not same size
    std::cout << std::hex << std::uppercase << *type << "\n";
    
    ArrayCast<unsigned int, 2u> ac_long;
    ac_long[0] = 1;
    ac_long[1] = 0xF;
    unsigned long *long_val = ac_long.cast<unsigned long>();
    std::cout << "Long value is: " << std::hex << std::uppercase << *long_val << "\n";
 
    for(unsigned int i = 0; i < ac_long.array_size(); ++i)
        std::cout << "Int: " << i << " = " << std::hex << std::uppercase << ac_long[i] << "\n";
    
    unsigned char *bytes = ac_long.bytes();
    for(unsigned int i = 0; i < ac_long.size_bytes(); ++i) {
        std::cout << "Byte: "<< i << " = " << std::hex << std::uppercase << int(bytes[i]) << "\n";
    }
    return 0;
}
