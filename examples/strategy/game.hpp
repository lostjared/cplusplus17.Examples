#ifndef _GAME_H_PP
#define _GAME_H_PP
#include<string>
#include<algorithm>
#define DEBUG_MODE 

namespace game {

    struct Color {
        unsigned char r,g,b;
        Color() = default;
        Color(unsigned char r, unsigned char g, unsigned char b);
    };

    enum Key { KEY_LEFT=1, KEY_RIGHT, KEY_UP, KEY_DOWN };

    using Font = int;
    using Image = int;

    struct RenderObject {
        virtual ~RenderObject() = default;
        virtual void drawAt(Image image, int x, int y) = 0;
        virtual void drawAtRect(Image image, int x, int y, int w, int h) = 0;
        virtual void drawAtRect(Image image, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) = 0;
        virtual void printText(Font font, int x, int y, const std::string &text, const Color &col) = 0;
        virtual Font loadImage(const std::string &text) = 0;
        virtual void setImageColorKey(Image image, const Color &c) = 0;
        virtual Image loadFont(const std::string &text, int size) = 0;
        virtual unsigned int getTicks() = 0;
        virtual bool keyDown(const Key &c) = 0;
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