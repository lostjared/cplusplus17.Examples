#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

#include"level.hpp"
#include"game.hpp"
namespace game {
     class GameLevel : public GameObject {
    public:
        GameLevel() = default;
        void init(RenderObject *ro) override;
        void draw(RenderObject *ro) override;
        void keydown(char key) override;
        void keyup(char key) override;   

    protected:    
        Level level;
        Camera cam;
        Image brick;
        Font arial;
        int tsize;
        float delta;
        const int TILE_W=16;
        static const int WINDOW_SIZE_W = 1280/16;
        static const int WINDOW_SIZE_H = 720/16;
    };
}














#endif