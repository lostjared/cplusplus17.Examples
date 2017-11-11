#include<iostream>
#include<string>
#include<vector>
#include<memory>

// only change through create new object
class User {
public:
    User(const std::string &firstn, const std::string &lastn, const bool &en) : first(firstn), last(lastn), enabled(en) {}
    std::string getFirst() const { return first; }
    std::string getLast() const { return last; }
    bool getEnabled() const { return enabled; }
private:
    std::string first, last;
    bool enabled;
};

// create List with recursion
template<typename Iter, typename Func>
void createList(bool enabled, std::vector<std::string> &l, std::vector<User> &users, Iter index, Func func) {
    if(index != users.end()) {
        if(index->getEnabled() == enabled) l.push_back(func(*index));
    	createList(enabled, l, users, index+1, func);
    }
}

// enable all in list with recursion
template<typename Iter>
void updateListEnableAll(bool enabled, std::vector<User> &u, Iter index) {
    if(index != u.end()) {
        *index = User(index->getFirst(), index->getLast(), index->getEnabled());
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
    std::vector<User> users { {"Jared", "Bruni", true},  { "Pink", "Floyd",true}, {"Black", "Sabbath",true}, {"David", "Bowie", false}};
    std::vector<std::string> first_name, all_last;
    createList(true, first_name, users, users.begin(), [](auto &u) -> std::string { return u.getFirst(); });
    updateListEnableAll(true,users,users.begin());
    createList(true, all_last, users, users.begin(), [](auto &u) -> std::string { return u.getLast(); });
    printList(first_name.begin(), first_name.end());
    printList(all_last.begin(), all_last.end());
    return 0;
}
