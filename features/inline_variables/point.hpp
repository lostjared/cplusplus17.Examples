#ifndef __POINT_H__
#define __POINT_H__

#include"header_only.hpp"

namespace point {
    
    class Point {
        int x,y;
    public:
        void set(int xx, int yy);
        void get(int &xx, int &yy);
    };
}






#endif
