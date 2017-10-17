#include<iostream>
#include<string>

template<typename... Args>
class Character : public Args... {
public:
    Character(Args... args) : Args(args)... {}
};

struct Point {
    double x,y,z;
};

class User {
    std::string name;
public:
    User(const std::string &n) : name(n) {
        std::cout << "Set name to: " << name << "\n";
    }
};

class Draw {
public:
    Draw() = default;
    void drawAt(unsigned int screen_x, unsigned int screen_y) {
        // draw
        std::cout << "Draw command: " << screen_x << ":" << screen_y << "..\n";
    }
private:
    // character images
};

int main() {
    Character<Point,User,Draw> hero({0, 0, 1},User("Jared"), Draw());
    hero.drawAt(100, 100);
    return 0;
}
