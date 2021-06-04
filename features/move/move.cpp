#include<iostream>
#include<string>
#include<utility>

class User {
public:
    User() = default;
    User(std::string n) : name{n} {}
    ~User() = default;
    User(const User &u) : name {u.name} {
        std::cout << "** copy constructor \n";
    }
    User(User &&u) : name {std::move(u.name)} {
        std::cout << "** move cønstructor \n";
    }
    User &operator=(const User &u) {
        name = u.name;
        std::cout << "** operator = &\n";
        return *this;
    }
    User &operator=(User &&u) {
        std::cout << "** operator = &&\n";
        name = std::move(u.name);
        return *this;
    }
    std::string getName() && { return std::move(name); }
    const std::string &getName() const & { return name; }
protected:
    std::string name;
};

User newName(std::string name) {
    return User(name);
}

int main() {
    std::cout << newName("hello").getName() << "\n";
    for (char c : newName("test").getName()) {
        std::cout << c << "\n";
    }
    User u("test 1 2 3");
    std::cout << u.getName() << "\n";
    User u2 { std::move(u) };
    std::cout << u2.getName() << "\n";
    User u3;
    u3 = u2;
    std::cout << u3.getName() << "\n";
    u3 = User("test 1 3 3 4");
    std::cout << u3.getName() << "\n";
    return 0;
}
