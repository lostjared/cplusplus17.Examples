#ifndef _LEVEL_H__
#define _LEVEL_H__
#include<cstdint>
#include<iostream>
#include<string>

namespace game {

    struct Tile {
        Tile() = default;
        int32_t x = 0;
        int32_t y = 0;
        int32_t w = 0;
        int32_t h = 0;
        int32_t color = 0;
        int32_t solid = 0;
        int32_t img = 0;
    };

    class Camera {
    public:
        Camera() = default;
        Camera(int w, int h, int mx, int my);
        void init(int w, int h, int mx, int my);
        void move(float delta, float dx, float dy);
        int getx() const;
        int gety() const;
        int get_width() const;
        int get_height() const;
protected:    
        int x,y,width,height,max_x,max_y,speed_x,speed_y;
    };

    class Level {
    public:
        Level();
        ~Level();
        bool loadLevel(const std::string &filename);
        int width, height;
        void create(int w, int h, const Tile &init_tile);
        Tile *at(int x, int y);
        void output_map(std::ostream &out);
    protected:
        Tile **tiles;
        bool resizeTiles(int w, int h);
        void releaseTiles();
    };

    static const int WINDOW_SIZE_WIDTH = 1280;
    static const int WINDOW_SIZE_HEIGHT = 720;
}

#endif