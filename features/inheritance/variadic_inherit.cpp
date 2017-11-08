#include<iostream>
#include<string>

template<typename... Base>
class Object : public Base... {
public:
    Object(Base... args) : Base(args)... {}

    void say(std::string s) {
        std::cout << s << "\n";
    }
};

class X {
public:
    X(std::string value) : x(value) {}
    void sayX() {
        std::cout << "say: " << x << "\n";
    }
private:
    std::string x;
};

class Y {
public:
    Y(std::string value) : y(value) {}
    void sayY() {
        std::cout << "say: " << y << "\n";
    }
private:
    std::string y;
};
                                          
int main() {
    Object<X,Y> object(X("Hello, "), Y("World!"));
    object.say("Hello World!");
    object.sayX();
    object.sayY();
    return 0;
}
