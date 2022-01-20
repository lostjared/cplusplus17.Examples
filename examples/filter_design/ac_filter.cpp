#include "ac_filter.hpp"

namespace ac {

    unsigned char wrap_cast(double d) {
        unsigned long val = static_cast<unsigned long>(d);
        if(val > 255)
            val = val%255;
        return static_cast<unsigned char>(val);
    }


    AC_Filter::AC_Filter(const std::string &n) : name{n} {
        filters.push_back(this);
        map_filter[n] = this;
    }

    void AC_Filter::exec(cv::Mat &frame) {
       // args.collection.shiftFrames(frame);
        proc(frame, args);
    }

    std::string AC_Filter::get_name() const {
        return name;
    }

    void AC_Filter::setalpha(double d) {
        args.alpha = d;
    }

    void AC_Filter::Args::move_in_out() {
        if(dir == true) {
            alpha += 0.01;
            if(alpha >= 5.0)
                dir = false;
        } else {
            alpha -= 0.01;
            if(alpha <= 1.0)
                dir = true;
        }
    }

    AC_Filter::Args AC_Filter::args;
    std::vector<AC_Filter *> filters;
    std::unordered_map<std::string, AC_Filter *> map_filter;
}

