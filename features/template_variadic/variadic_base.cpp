#include<iostream>

class User {
public:
    User(const std::string &xname, const std::string &xnumber) : name(xname), number(xnumber) {
        
    }
    std::string getName() const { return name; }
    std::string getNumber() const { return number; }
    
private:
    std::string name, number;
    
};

class OutputNumber {
public:
    void printNumber(const User &u) { std::cout << u.getNumber() << "\n"; }
};

class OutputName {
public:
    void printName(const User &u) { std::cout << u.getName() << "\n"; }
};

template<typename... Bases>
class DB : public Bases... {
public:
    
};

int main() {
    User u("Jared", "1920858482");
    
    DB<OutputNumber,OutputName> p1;
    p1.printNumber(u);
    p1.printName(u);
    
    DB<OutputName> p2;
    p2.printName(u);
    return 0;
}
