#include "game_level.hpp"
#include<sstream>
#include<iostream>
#include<string>

namespace game {

  void GameLevel::init(RenderObject *ro) {
        int max_x = ((WINDOW_SIZE_W*2) * 16 - WINDOW_SIZE_WIDTH) -1;
        int max_y = ((WINDOW_SIZE_H*2) * 16 - WINDOW_SIZE_HEIGHT) -1;
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
        arial = ro->loadFont("./img/arial.ttf", 24);
        delta = 0;
    }

    void GameLevel::draw(RenderObject *ro) {
        int start_col = cam.getX() / tsize;
        int end_col = start_col + (cam.getWidth() / tsize);
        int start_row = cam.getY() / tsize;
        int end_row = start_row + (cam.getHeight() / tsize);

        int cx = cam.getX();
        int cy = cam.getY();

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

        unsigned int tick = ro->getTicks();
        static unsigned int prev_tick = 0;
        delta = float(tick-prev_tick)/1000;
        prev_tick = tick; 
        if(ro->keyDown(Key::KEY_RIGHT)) {
            cam.move(std::min(0.009f, delta), 1.0f, 0.0f);
        } else if(ro->keyDown(Key::KEY_LEFT)) {
            cam.move(std::min(0.009f, delta), -1.0f, 0.0f);
        }
        if(ro->keyDown(Key::KEY_UP)) {
            cam.move(std::min(0.009f, delta), 0.0f, -1.0f);
        } else if(ro->keyDown(Key::KEY_DOWN)) {
            cam.move(std::min(0.009f, delta), 0.0f, 1.0f);
        }
#ifdef DEBUG_MODE
        unsigned int tc = tick / 1000;
        static unsigned int pv = 0;
        static unsigned int frame_c = 0;
        static int frame_counter = 0;
        if(tc > pv) {
            pv = tc;
            frame_counter = frame_c;
            frame_c = 0;
        } else {
            frame_c += 1;
        }
        std::ostringstream frame_count;
        frame_count << frame_counter << " FPS Camera: X: " << cam.getX() << " - Y: " << cam.getY();
        ro->printText(arial, 15, 15, frame_count.str(), Color(255,255,255));
#endif
    }
     
    void GameLevel::keydown(char key) {

  
    }
     
    void GameLevel::keyup(char key) {

    }        
}