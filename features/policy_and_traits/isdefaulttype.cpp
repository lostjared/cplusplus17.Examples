//Based on C++ Templates Complete Guide: Second Edition Chapter 19 section 19.8.1

#include<iostream>
#include<string>
#include<type_traits>

template<typename T>
class isBuiltIn : public std::false_type {
public:
    
};

#define BUILT_IN(T) \
			template<> class isBuiltIn<T> : public std::true_type { \
                    	public: \
						};


BUILT_IN(long double)
BUILT_IN(double)
BUILT_IN(float)
BUILT_IN(unsigned long long)
BUILT_IN(signed long long)
BUILT_IN(unsigned long)
BUILT_IN(signed long)
BUILT_IN(unsigned int)
BUILT_IN(signed int)
BUILT_IN(unsigned short)
BUILT_IN(signed short)
BUILT_IN(unsigned char)
BUILT_IN(signed char)
BUILT_IN(wchar_t)
BUILT_IN(char16_t)
BUILT_IN(char32_t)
BUILT_IN(bool)
BUILT_IN(void)


template<typename T>
void isType(const T &type) {
    if constexpr(isBuiltIn<T>::value) {
        std::cout << "Yes it is a built in type...\n";
    } else {
        std::cout << "No it is not a built in type...\n";
    }
}

template<typename T, typename... Args>
void isType(const T &type, Args... args) {
    isType(type);
    isType(args...);
}

int main() {
    int a = 100;
    long b = 200;
    std::string test = "Hello";
    short c = 55;
    unsigned long long cpp = 100;
    isType(a,b,test,c,cpp);
    return 0;
}
