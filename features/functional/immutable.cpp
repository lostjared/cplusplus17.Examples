#include<iostream>
#include<string>
#include<vector>
#include<memory>

// only change through creating a new object
class User {
public:
    User(const std::string &firstn, const std::string &lastn, const bool &en) : first(firstn), last(lastn), enabled(en) {}
    std::string getFirst() const { return first; }
    std::string getLast() const { return last; }
    bool getEnabled() const { return enabled; }
private:
    const std::string first, last;
    const bool enabled;
};

// create List with recursion
template<typename Iter, typename Func>
void createList(bool enabled, std::vector<std::string> &l, std::vector<std::unique_ptr<User>> &users, Iter index, Func func) {
    if(index != users.end()) {
        User *u = (*index).get();
        if(u->getEnabled() == enabled) l.push_back(func(*u));
    	createList(enabled, l, users, index+1, func);
    }
}

// enable all in list with recursion
template<typename Iter>
void updateListEnableAll(bool enabled, std::vector<std::unique_ptr<User>> &u, Iter index) {
    if(index != u.end()) {
        User *user = (*index).get();
        index->reset(new User(user->getFirst(), user->getLast(), user->getEnabled()));
        updateListEnableAll(enabled, u, index+1);
    }
}
// print the list with recursion
template<typename Iter>
void printList(Iter start, Iter stop) {
    if(start != stop) {
        std::cout << "value is:  " << *start << "\n";
        printList(start+1, stop);
    }
}
// main function
int main() {
    User *user[] = {new User("Jared", "Bruni", true), new User("Pink", "Floyd", true), new User("Black", "Sabbath", true),
        new User("David", "Bowie", false), nullptr };
    std::vector<std::unique_ptr<User>> users;
    for(unsigned int i = 0; user[i] != 0; ++i)
         users.push_back(std::unique_ptr<User>(user[i]));
    
    std::vector<std::string> first_name, all_last;
    createList(true, first_name, users, users.begin(), [](auto &u) -> std::string { return u.getFirst(); });
    updateListEnableAll(true,users,users.begin());
    createList(true, all_last, users, users.begin(), [](auto &u) -> std::string { return u.getLast(); });
    printList(first_name.begin(), first_name.end());
    printList(all_last.begin(), all_last.end());
    return 0;
}
