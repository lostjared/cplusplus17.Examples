#include"header_only.hpp"
#include "point.hpp"
#include<iostream>

int main(int argc, char **argv) {
    std::cout << "Hello C++17!\n";
    int x = 0,y = 0,w = 0,h = 0;
    square::background.get(x,y,w,h);
    std::cout << "Rect is: " << x << ", " << y << ", " << w << ", " << h << "\n";
    return 0;
}
