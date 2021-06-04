#include<iostream>
#include<string>

class User {
public:
    User(std::string n) : name{n} {
        
    }
    void setName(const std::string &n) {
        name = n;
    }
    // for move
    std::string getName() && {
        return std::move(name);
    }
    const std::string &getName() const& {
        return name;
    }
    
protected:
    std::string name;
    
};

User getUser() {
    return User("value");
}

int main() {
    std::cout << "Enter name: ";
    std::string n;
    std::cin >> n;
    User u(n);
    std::cout << "Your name: " << u.getName() << "\n";
    for(char c : u.getName()) {
        std::cout << c << "\n";
    }
    for(char c : getUser().getName()) {
        std::cout << c << "\n";
    }
    std::cout << getUser().getName() << "\n";
    return 0;
}
