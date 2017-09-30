/* Concept from "C++ Templates the Complete Guide: Second Edition
 Chapter 6
 
 Using std::forward and std::enable_if_t
 
 */


#include<iostream>
#include<utility>
#include<string>
#include<type_traits>
#include<algorithm>

template<typename T>
using enable_string = std::enable_if_t<std::is_convertible<T,std::string>::value>;

class User {
public:
    template<typename S, typename = enable_string<S>>
    explicit User(S&& str) : name(std::forward<S>(str)) {
        std::cout << "Called String&&\n";
    }
    User(const User &u) : name(u.name) {
        std::cout << "Called &\n";
    }
    User(User &&p) : name(std::move(p.name)) {
        std::cout << "Called User &&\n";
    }
    void print() {
        std::cout << "My Username is: " << name << "\n";
    }
private:
    std::string name;
};

int main() {
    std::string username;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
   	User u1(username);
    User u2("temporary");
    User u3(u1);
    User u4(std::move(u1));
    u2.print();
    u3.print();
    u4.print();
    return 0;
}
