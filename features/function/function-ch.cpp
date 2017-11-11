
#include<iostream>
#include<string>
#include<vector>
#include<functional>

class User {
public:
    std::string first, last;
    bool enabled;
};

std::vector<User> users { {"Jared", "Bruni", true}, {"Person", "Unknown", false}, {"Test1", "Test2",false}, {"Mr. ", "Robot", true}};

// could do it like this
void createListOfFirstNames(std::vector<std::string> &u) {
    for(auto i  = users.begin(); i != users.end(); ++i) {
        if(i->enabled) u.push_back(i->first);
    }
}

void createListOfLastName(std::vector<std::string> &u) {
    for(auto i  = users.begin(); i != users.end(); ++i) {
        if(i->enabled) u.push_back(i->first);
    }
}

// but less typing like this
template<typename F>
void createList(std::vector<std::string> &u,F func) {
    for(auto i = users.begin(); i != users.end(); ++i) {
        if(i->enabled == true) u.push_back(func(*i));
    }
}

int main() {
    std::vector<std::string> first, last;
    createList(first, [](User &u) -> std::string {
        return u.first;
    });
    createList(last, [](User &u) -> std::string {
        return u.last;
    });
    for(auto &i : first) std::cout << i << "\n";
    for(auto &i : last) std::cout << i << "\n";
    return 0;
}
