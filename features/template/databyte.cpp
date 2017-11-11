/*
 create a type that can be changed through manipulating each byte
 kind of like a bitset but for bytes not bits.
 
 http://lostsidedead.com
*/


#include<iostream>
#include<string>
#include<type_traits>

template<typename T>
class DataBytes {
public:
    static_assert(std::is_fundamental<T>::value, "Value not built in type");
    DataBytes(const T &type);
    DataBytes(const DataBytes<T> &value);
    DataBytes(DataBytes<T> &&value);
    DataBytes<T> &operator=(const T &type);
    DataBytes<T> &operator=(const DataBytes<T> &byte);
    DataBytes<T> &operator=(const DataBytes<T> &&r);
    
    unsigned char &at(unsigned int pos);
    unsigned char &operator[](unsigned int pos) { return at(pos); }
    T value () const { return bytes.type; }
    template<typename T2>
    T2 *cast() {
        return reinterpret_cast<T2*>(bytes.byteval);
    }
    
private:
    union {
        T type;
        unsigned char byteval[sizeof(T)];
    } bytes;
};


template<typename T>
DataBytes<T>::DataBytes(const T &type) {
    bytes.type = type;
}

template<typename T>
DataBytes<T>::DataBytes(const DataBytes<T> &value) {
    bytes = value.bytes;
}

template<typename T>
DataBytes<T>::DataBytes(DataBytes<T> &&value) {
    bytes = std::move(value.bytes);
}

template<typename T>
DataBytes<T> &DataBytes<T>::operator=(const DataBytes<T> &byte) {
    bytes = byte.byteval;
}

template<typename T>
DataBytes<T> &DataBytes<T>::operator=(const DataBytes<T> &&r) {
    bytes = std::move(r.bytes);
}
template<typename T>
DataBytes<T>  &DataBytes<T>::operator=(const T &type) {
    bytes.value = type;
}

template<typename T>
unsigned char &DataBytes<T>::at(unsigned int pos) {
    return bytes.byteval[pos];
}

int main() {
    DataBytes<unsigned int> b(0xFFFFFF);
    // line below will fail at compile time because
    // it requires a fundamental type
    //DataByte<std::string> test;
    std::cout << std::hex << b.value() << "\n";
    b[1] = 0;
    std::cout << std::hex << b.value() << "\n";
    return 0;
}
