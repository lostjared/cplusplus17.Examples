
#include<iostream>
#include<string>
#include<vector>
#include<functional>

class User {
public:
    std::string first, last;
    bool enabled;
};

// could do it like this
void createListOfFirstNames(std::vector<User> &users, std::vector<std::string> &u) {
    for(auto i  = users.begin(); i != users.end(); ++i) {
        if(i->enabled) u.push_back(i->first);
    }
}
void createListOfLastName(std::vector<User> &users, std::vector<std::string> &u) {
    for(auto i  = users.begin(); i != users.end(); ++i) {
        if(i->enabled) u.push_back(i->first);
    }
}

// but less typing like this
// pure function - only operates on types passed in as arguments
template<typename F>
void createList(bool enabled, std::vector<User> &users, std::vector<std::string> &u,F func) {
    for(auto i = users.begin(); i != users.end(); ++i) {
        if(i->enabled == enabled) u.push_back(func(*i));
    }
}

int main() {
    std::vector<User> users { {"Jared", "Bruni", true}, {"Person", "Unknown", false}, {"Test1", "Test2",false}, {"Mr. ", "Robot", true}};
    std::vector<std::string> first, last,disabledfirst;
    createList(true, users, first, [](User &u) -> std::string { return u.first; });
    createList(true, users, last, [](User &u) -> std::string { return u.last; });
    createList(false, users, disabledfirst, [](User &u) -> std::string { return u.first; });
    for(auto &i : first) std::cout << i << "\n";
    for(auto &i : last) std::cout << i << "\n";
    for(auto &i : disabledfirst) std::cout << i << "\n";
    return 0;
}
