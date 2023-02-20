#include"level.hpp"
#include<iostream>

namespace game {

   Camera::Camera(int w, int h, int mx, int my) : x{0}, y{0}, width{w}, height{h}, max_x{mx}, max_y{my}, speed{512} {}

   void Camera::init(int w, int h, int mx, int my) {
        x = 0;
        y = 0;
        width = w;
        height = h;
        max_x = mx;
        max_y = my;
        speed = 1280;
   }

   void Camera::move(float delta, float dx, float dy) {
        float dx_val = dx * speed * delta;
        float dy_val = dy * speed * delta;
        x += static_cast<int>(dx_val);
        y += static_cast<int>(dy_val);
        x = std::max(0, std::min(x, max_x));
        y = std::max(0, std::min(y, max_y));
   }


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
        int max_x = ((WINDOW_SIZE_W*2) * 16 - 1280) -1;
        int max_y = ((WINDOW_SIZE_H*2) * 16 - 720) -1;
        tsize = 16;
        cam.init(1280, 720, max_x, max_y);
        level.create(WINDOW_SIZE_W*2, WINDOW_SIZE_H*2, Tile{});
        for(int i = 0; i < WINDOW_SIZE_W*2; ++i) {
            for(int z = 0; z < WINDOW_SIZE_H*2; ++z) {
                Tile *t = level.at(i, z);
                t->img = rand()%2;
            }
        }
        std::cout << "Created: " << level.width << ":" << level.height << "\n";
        brick = ro->loadImage("img/brick.bmp");
    }

    void GameLevel::draw(RenderObject *ro) {

        int start_col = cam.x / tsize;
        int end_col = start_col + (cam.width / tsize);
        int start_row = cam.y / tsize;
        int end_row = start_row + (cam.height / tsize);

        int cx = cam.x;
        int cy = cam.y;

        int off_x = -cx + start_col * tsize;
        int off_y = -cy + start_row * tsize;

        for(int x = start_col; x < end_col; ++x) {
            for(int y = start_row; y < end_row; ++y) {
                Tile *tile = level.at(x, y);
                if(tile != nullptr && tile->img != 0) {
                    int xx = (x - start_col) * tsize + off_x;
                    int yy = (y - start_row) * tsize + off_y;
                    ro->drawAt(brick, xx, yy);                 
                }
            }
        }        
    }
     
    void GameLevel::keydown(char key) {
        if(key == 's') {
            cam.move(0.009f, 1.0f, 0.0f);
        } else if(key == 'a') {
            cam.move(0.009f, -1.0f, 0.0f);
        }
    }
     
    void GameLevel::keyup(char key) {

    }        

}