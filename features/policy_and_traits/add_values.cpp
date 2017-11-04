/*
 	Policy and Traits classes
	 based on "C++ Templates the Complete Guide: Second Edition"
*/

#include<iostream>
#include<vector>
#include<string>

template<typename T>
class ValueTraits;

template<>
class ValueTraits<char> {
public:
    using Type = int;
    static constexpr int zero() { return 0; }
    
};

template<>
class ValueTraits<int> {
public:
    using Type = long;
    static constexpr int zero() { return 0; }
};

template<>
class ValueTraits<long> {
public:
    using Type = long;
    static constexpr int zero() { return 0; }
};

template<>
class ValueTraits<float> {
public:
    using Type = float;
    static constexpr float zero() { return 0; }
};

template<>
class ValueTraits<std::string> {
public:
    using Type = std::string;
    static std::string zero() { return ""; }
};

template<typename T>
class ValuePolicy;

template<>
class ValuePolicy<char> {
public:
    static int add(int start, int val) {
        return (start+val);
    }
};

template<>
class ValuePolicy<int> {
public:
    static long add(int start, int val) {
        return (start+val);
    }
};

template<>
class ValuePolicy<long> {
public:
    static long add(long start, long val) {
        return (start+val);
    }
};

template<>
class ValuePolicy<float> {
public:
    static float add(float start, float val) {
        return (start+val);
    }
};

template<>
class ValuePolicy<std::string> {
public:
    static std::string add(std::string start, std::string val) {
        std::string value = start;
        value += val;
        return value;
    }
};

template<typename T, typename Iter, typename Policy = ValuePolicy<T>>
auto addValues(Iter start, Iter stop) {
    using Type = typename ValueTraits<T>::Type;
    Type type = ValueTraits<T>::zero();
    while(start != stop) {
        type = ValuePolicy<T>::add(type, *start);
        start++;
    }
    return type;
}

int main(){
    std::vector<int> values {5,5,5,5};
    long result = addValues<int>(values.begin(), values.end());
    std::cout << "Value: " << result << "\n";
    std::vector<std::string> string_values {"Hello, ", "World!", " with ", " Traits!\n"};
    std::string string_result = addValues<std::string>(string_values.begin(), string_values.end());
    std::cout << "String concat: " << string_result << "\n";
    return 0;
}
