#include<iostream>
#include<string>

class Functor {
public:
    Functor(std::string v) : value(v) {}
    
    bool operator()(std::string cmp) {
        bool v = (value == cmp);
        if(v)
            std::cout << "Comparision Equal...\n";
        else
            std::cout << "Comparision Not Equal...\n";
        return v;
    }
    
private:
    std::string value;
};

template<typename F>
bool TestValue(F f, std::string v) {
    return f(v);
}

int main() {
    TestValue(Functor("Hello World"), "Hello World");
    Functor f("Test");
    TestValue(f, "Hey");
    f("hey");
    return 0;
}
