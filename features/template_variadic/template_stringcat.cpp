// variadic string concat function template
// written by Jared Bruni

#include<iostream>
#include<string>
#include<sstream>

template<typename T>
void string_cat(std::string &s, const T &type) {
    std::ostringstream stream;
    stream << type;
    s += stream.str();
}

template<typename T,typename... Args>
void string_cat(std::string &s,const T &obj,Args... args) {
    string_cat(s, obj);
    string_cat(s, args...);
}

int main() {
    std::string value;
    string_cat(value, "Hello ", "World: ", 100, " ", 200, " float: ", 200.5, "\n");
    std::cout << value;
    return 0;
}
