#include"level.hpp"
#include<iostream>

namespace game {

    Level::Level() : width{0}, height{0}, tiles{nullptr} {

    }

    Level::~Level() {
        releaseTiles();
    }

    bool Level::loadLevel(const std::string &filename) {

        return true;
    }

    void Level::create(int w, int h, const Tile &init_tile) {
        resizeTiles(w, h);
        for(int i = 0; i < w; ++i) {
            for(int z = 0; z < h; ++z) {
                tiles[i][z] = init_tile;
            }
        }
    }

    Tile *Level::at(int x, int y) {
        if(x >= 0 && x < width && y >= 0 && y < height) {
            return &tiles[x][y];
        }
        return nullptr;
    }

    void Level::output_map(std::ostream &out) {
        if(width == 0 || height == 0 || tiles == nullptr) {
            out << "[empty map]\n";
            return;
        }
        for(int x = 0; x < width; ++x) {
            for(int y = 0; y < height; ++y) {
                Tile *t = at(x,y);
                if(t != nullptr) {
                     out << "x: " << x << ", y: " << y << " " << t->color << "\n";
                }
            }
        }
    }

    bool Level::resizeTiles(int w, int h) {
        releaseTiles();
        width = w;
        height = h;
        tiles = new Tile*[width];
        for(int i = 0; i < width; ++i) {
            tiles[i] = new Tile[height];
        }
        return true;
    }

    void Level::releaseTiles() {
        if(tiles != nullptr && width != 0) {
            for(int i = 0; i < width; ++i) {
                delete [] tiles[i];
            }
            delete [] tiles;
        }
    }

    void GameLevel::init(RenderObject *ro) {
        level.create(WINDOW_SIZE_W*2, WINDOW_SIZE_H*2, Tile{});
        std::cout << "Created: " << level.width << ":" << level.height << "\n";
        brick = ro->loadImage("img/brick.bmp");
    }

    void GameLevel::draw(RenderObject *ro) {
            for(int z = 0; z < WINDOW_SIZE_H; ++z) {
                for(int i = 0; i < WINDOW_SIZE_W; ++i) {
                    ro->drawAt(brick, i*TILE_W, z*TILE_W);
                }
            }
    }
     
    void GameLevel::keydown(char key) {

    }
     
    void GameLevel::keyup(char key) {

    }        

}