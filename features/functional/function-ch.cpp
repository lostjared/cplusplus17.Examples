
#include<iostream>
#include<string>
#include<vector>
#include<functional>

class User {
public:
    std::string first, last;
    bool enabled;
};

// could take this approach but lots of typing
void createListOfFirstNames(std::vector<User> &users, std::vector<std::string> &u) {
    for(auto i  = users.begin(); i != users.end(); ++i) {
        if(i->enabled) u.push_back(i->first);
    }
}
void createListOfLastName(std::vector<User> &users, std::vector<std::string> &u) {
    for(auto i  = users.begin(); i != users.end(); ++i) {
        if(i->enabled) u.push_back(i->last);
    }
}

void createListODisabledFirstName(std::vector<User> &users, std::vector<std::string> &u) {
    for(auto i  = users.begin(); i != users.end(); ++i) {
        if(i->enabled == false) u.push_back(i->first);
    }
}
void createListOfDisabledLastName(std::vector<User> &users, std::vector<std::string> &u) {
    for(auto i  = users.begin(); i != users.end(); ++i) {
        if(i->enabled == false) u.push_back(i->last);
    }
}

// but less typing like this
// using first class function (passed as parameter)
// In computer science, a programming language is said to have first-class functions if it treats functions as first-class citizens.
// This means the language supports passing functions as arguments to other functions, returning them as the values from other functions,
// and assigning them to variables or storing them in data structures
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
