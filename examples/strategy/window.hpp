#ifndef _GAME_H__P
#define _GAME_H__P

#include<string>
#include"game.hpp"

namespace game {

    class Window {
    public:
        Window() = default;
        static bool createWindow(const std::string &title, int w, int h);
        static void setObject(GameObject *obj);
        static int loop();
        static void quit();
        static void init_object(GameObject *obj);
    protected:
        static bool active;
        static GameObject *current_object;
    };
    unsigned int getTicks();
}

#endif
