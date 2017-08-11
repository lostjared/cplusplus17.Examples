#include "point.hpp"

namespace point {
    
    void Point::set(int xx, int yy) {
        x = xx;
        y = yy;
    }

    void Point::get(int &xx, int &yy) {
        xx = x;
        yy = y;
    }
}
