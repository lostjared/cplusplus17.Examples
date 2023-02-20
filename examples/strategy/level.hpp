#ifndef _LEVEL_H__
#define _LEVEL_H__
#include<cstdint>
#include<iostream>
#include<string>
#include"game.hpp"

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
        Camera(int w, int h, int mx, int my);
        void move(float delta, float dx, float dy);
    protected:
        int x,y,width,height,max_x,max_y,speed;
    
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

    class GameLevel : public GameObject {
    public:
        GameLevel() = default;
        void init(RenderObject *ro) override;
        void draw(RenderObject *ro) override;
        void keydown(char key) override;
        void keyup(char key) override;    
    protected:    
        Level level;
        int brick;
        const int TILE_W=16;
        const int WINDOW_SIZE_W = 1280/TILE_W;
        const int WINDOW_SIZE_H = 720/TILE_W;
    };

}

#endif