#include"staticif.hpp"
#include<iostream>

static st::staticIF startup([](){
    std::cout <<  "seeding..\n";
    srand(static_cast<unsigned int>(time(0)));
}, [](){
    std::cout << "goodbye!\n";
});

int main(int argc, char **argv) {
    std::cout << "seeded random number: " << rand()%255 << "\n";
    return 0;
}

