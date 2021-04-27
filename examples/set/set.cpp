#include<iostream>
#include<set>
#include<string>

int main() {
    std::set<std::string> ideas;
    std::string idea;
    while(1) {
        std::cout << "Enter idea: ";
        std::getline(std::cin, idea);
        ideas.insert(idea);
        for(auto i = ideas.begin(); i != ideas.end(); ++i) {
            std::cout << *i << "\n";
             if(*i == "quit") exit(EXIT_SUCCESS);
        }
    }
    return 0;
}
