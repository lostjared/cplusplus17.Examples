#include<iostream>
#include<string>

class Thought {
public:
    std::string idea;
};

Thought &get(Thought &thought) {
    std::cout << "Got info: " << thought.idea << "\n";
    return thought;
}
Thought &give(Thought &thought) {
    std::cout << "Gave thought " << thought.idea << "\n";
    return thought;
}

void life() {
    Thought code;
    code.idea = "Cycle\n";
    Thought think = get(give(code));
    std::cout << "Karma returns: " << think.idea << "\n";
}


int main(int argc, char **argv) {
    while(1) {
        life();
    }
    return 0;
}
