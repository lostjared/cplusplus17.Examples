/*
 Learning from C++ Templates the Complete Guide: Second Edition
 Different ways you can use decltype
*/

#include<iostream>
#include<vector>

decltype(auto) f() {
    int r = 100;
    // below would return reference
    // return (r);
    return r;
}

// base return type on result of +
template<typename X, typename Y>
auto function(X value1, Y value2) -> decltype(value1+value2) {
    return value1+value2;
}

template<decltype(auto) Type> class X {
public:
    int arr[Type];
    int &operator[](unsigned int p) { return arr[p]; }
};

template<auto S>
int AddMult(decltype(S) value1, decltype(S) value2) {
    return (value1 + value2) * S;
}

int main() {
    /* following shows using decltype(auto) */
    std::vector<int>::iterator pos;
    std::vector<int> it_value { 100, 4, 2, 8 };
    pos = it_value.begin();
    // makes a copy of *pos
    auto element = *pos;
    // will fail if iterator returns the value
    auto &element1 = *pos;
    // redundent
    decltype(*pos) dat = *pos;
    // better
    decltype(auto) loc = *pos;
    std::cout << "Value is: " << loc << "\n";
    int person = 1;
    const int &xperson = person;
    // is reference of person
    decltype(auto) value = xperson;
    
    // paranethsis mean use reference
    decltype(auto) val2 = (person);
    std::cout << "Person is: " << person << " Val2: " << val2;
    val2 += 100;
    std::cout << " Now its: " << person << "\n";
    
    std::vector<int> values {0, 1, 4, 6, 8};
    // is int &
    decltype(auto) type = values[0];
    decltype(values) v;
    v.push_back(255);
    std::cout << "v[0] = " << v[0] << "\n";
    constexpr int cvar = 100;
    // decltype(auto) as template
    X<cvar> xval;
    xval[0] = 100;
    xval[1] = 200;
    std::cout << "X<cvar>::arr[1] = " << xval[1] << "\n";
    // use function with decltype for parameters
    int add1 = 100, add2 = 200, add_value;
    add_value = AddMult<100>(add1, add2);
    std::cout << "Result: " << add_value << "\n";
    return 0;
}
