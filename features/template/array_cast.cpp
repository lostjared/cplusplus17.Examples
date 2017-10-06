/*
 
 Testing casting inbetween certain types
 using templates and reinterpret_cast
 
*/


#include<iostream>

template<typename T, int S>
class ArrayCast {
public:
    ArrayCast() = default;
    T &operator[](unsigned int index) {
        return arr[index];
    }
    T *all() { return &arr[0]; }
    unsigned char *bytes() { return reinterpret_cast<unsigned char*>(&arr[0]); }
    unsigned int array_size() { return sizeof(arr); }
    // cast with compile time check to ensure same size
    template<typename T2>
    T2 *cast() {
        static_assert(sizeof(T2)==(sizeof(T)*S), "Wrong size");
        return reinterpret_cast<T2*>(arr);
    }
    
private:
    T arr[S];
};


int main() {
    ArrayCast<unsigned char, 4> ac;
    ac[0] = 255;
    ac[1] = 255;
    ac[2] = 255;
    ac[3] = 255;
    unsigned int *type = ac.cast<unsigned int>();
    //unsigned long *long_type = ac.cast<unsigned long>(); // will cause an error because not same size
    std::cout << *type << "\n";
    
    ArrayCast<unsigned int, 2> ac_long;
    ac_long[0] = 1;
    ac_long[1] = 1;
    unsigned long *long_val = ac_long.cast<unsigned long>();
    std::cout << "Long value is: " << *long_val << "\n";
 
    for(unsigned int i = 0; i < 2; ++i)
        std::cout << "Int: " << i << " = " << ac_long[i] << "\n";
    
    unsigned char *bytes = ac_long.bytes();
    for(unsigned int i = 0; i < ac_long.array_size(); ++i) {
        std::cout << "Byte: "<< i << " = " << int(bytes[i]) << "\n";
    }
    return 0;
}
