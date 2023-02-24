#include"camera.hpp"
#include"window_const.hpp"
namespace game {

   Camera::Camera(int w, int h, int mx, int my) : x{0}, y{0}, width{w}, height{h}, max_x{mx}, max_y{my}, speed_x{WINDOW_SIZE_WIDTH}, speed_y{WINDOW_SIZE_HEIGHT} {}

   void Camera::init(int w, int h, int mx, int my) {
        x = 0;
        y = 0;
        width = w;
        height = h;
        max_x = mx;
        max_y = my;
        speed_x = WINDOW_SIZE_WIDTH;
        speed_y = speed_x;// WINDOW_SIZE_HEIGHT;
   }

   void Camera::move(float delta, float dx, float dy) {
        float dx_val = dx * speed_x * delta;
        float dy_val = dy * speed_y * delta;
        x += static_cast<int>(dx_val);
        y += static_cast<int>(dy_val);
        x = std::max(0, std::min(x, max_x));
        y = std::max(0, std::min(y, max_y));
   }
   
   int Camera::getX() const { 
        return x; 
   }
   
   int Camera::getY() const {
        return y; 
   }
   
   int Camera::getWidth() const { 
        return width; 
    }
   
   int Camera::getHeight() const { 
        return height; 
    }

    void Camera::reset() {
        x = y = 0;
    }
}