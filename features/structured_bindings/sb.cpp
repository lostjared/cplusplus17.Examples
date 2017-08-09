/// This is untested doesn't have compiler support yet
// but Structured bindings will break pair, tuple, struct into separete variables


#include<iostream>
#include<utility>

// just for getting a value
std::pair<std::string, int> getValue() {
    std::pair<std::string, int> p("Jared", 100);
    return p; // RVO
}


int main(int argc, char **argv) {
    std::cout << "Test program.\n";
    auto [first, second] = getValue(); // any pair variable
    std::cout << "First: " << first << " Second: " << second << "\n";
    return 0;
}
