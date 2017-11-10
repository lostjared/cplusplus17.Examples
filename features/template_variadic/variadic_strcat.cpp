#include<iostream>
#include<string>
#include<sstream>

class StringCat {
public:
    template<typename T>
    void operator()(std::string &s, const T &type) {
        stream << type;
        s += stream.str();
        stream.str("");
    }
    
    template<typename T, typename... Args>
    void operator()(std::string &s, const T &type, Args... args) {
        this->operator()(s, type);
        this->operator()(s, args...);
    }
private:
    std::ostringstream stream;
};

StringCat string_cat;


int main() {
    std::string value1, value2 = "World!";
    string_cat(value1, "Hello, ", value2, " ", 0xFF);
    std::cout << "String cat = " << value1 << "\n";
    return 0;
}
