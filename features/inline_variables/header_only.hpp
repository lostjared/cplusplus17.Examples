#ifndef HEADER_ONLY_H_
#define HEADER_ONLY_H_

#include<iostream>

namespace square {
    class Rect {
        int x, y, w, h;
    public:
        
        Rect() = default;
        Rect(int xx, int yy, int ww, int hh) : x(xx), y(yy), w(ww), h(hh) {}
        
        void set(int xx, int yy, int ww, int hh) {
            x = xx;
            y = yy;
            w = ww;
            h = hh;
        }
        
        void get(int &xx, int &yy, int &ww, int &hh) {
            xx = x;
            yy = y;
            ww = w;
            hh = h;
        }
    };
    
    inline Rect background(0, 0, 640, 480);
}

#endif
