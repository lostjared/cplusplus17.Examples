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

    class GameLevel;

    class Camera {
    public:
        Camera() = default;
        Camera(int w, int h, int mx, int my);
        void init(int w, int h, int mx, int my);
        void move(float delta, float dx, float dy);
    protected:
        int x,y,width,height,max_x,max_y,speed_x,speed_y;
        friend class GameLevel;    
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
        friend class Camera;
    protected:    
        Level level;
        Camera cam;
        int brick;
        int arial;
        int tsize;
        float delta;
        const int TILE_W=16;
        static const int WINDOW_SIZE_W = 1280/16;
        static const int WINDOW_SIZE_H = 720/16;
    };

    static const int WINDOW_SIZE_WIDTH = 1280;
    static const int WINDOW_SIZE_HEIGHT = 720;
}

#endif