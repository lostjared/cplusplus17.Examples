#include"window.hpp"
#include"level.hpp"
#include<iostream>


int main(int argc, char **argv) {
    if(!game::Window::createWindow("Game", 1280, 720)) {
        std::cerr << "Error on init.\n";
        return EXIT_FAILURE;
    }

    game::GameLevel level;
    game::Window::init_object(&level);
    game::Window::setObject(&level);
    return game::Window::loop();
}