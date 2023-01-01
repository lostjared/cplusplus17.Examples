#ifndef _GAME_H_PP
#define _GAME_H_PP
#include<string>

namespace game {

    struct Color {
        unsigned char r,g,b;
    };

    struct RenderObject {
        virtual ~RenderObject() = default;
        virtual void drawAt(int image, int x, int y) = 0;
        virtual void drawAtRect(int image, int x, int y, int w, int h) = 0;
        virtual void printText(int x, int y, const std::string &text, const Color &col) = 0;
        virtual int loadImage(const std::string &text) = 0;
    };

    struct GameObject {
        virtual ~GameObject() = default;
        virtual void init(RenderObject *ro) = 0;
        virtual void draw(RenderObject *ro) = 0;
        virtual void keydown(char key) = 0;
        virtual void keyup(char key) = 0;
    };
}

#endif