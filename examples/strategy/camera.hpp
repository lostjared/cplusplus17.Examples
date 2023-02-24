#ifndef _CAMERA_H__
#define _CAMERA_H__

#include<iostream>
#include<algorithm>

namespace game {

 class Camera {
    public:
        Camera() = default;
        Camera(int w, int h, int mx, int my);
        void init(int w, int h, int mx, int my);
        void move(float delta, float dx, float dy);
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        void reset();        
protected:    
        int x,y,width,height,max_x,max_y,speed_x,speed_y;
    };

}

#endif