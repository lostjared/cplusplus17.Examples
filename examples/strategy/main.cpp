#include"window.hpp"
#include"game_level.hpp"
#include<iostream>


int main(int argc, char **argv) {
    int width = 1280, height = 720;
    if(argc == 3) {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }
    if(!game::Window::createWindow("Game", width, height)) {
        std::cerr << "Error on init.\n";
        return EXIT_FAILURE;
    }
    game::GameLevel level;
    game::Window::init_object(&level);
    game::Window::setObject(&level);
    return game::Window::loop();
}