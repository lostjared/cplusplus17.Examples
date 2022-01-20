#include"selfalpha.hpp"

namespace ac {

    SelfAlpha::SelfAlpha() : AC_Filter("SelfAlpha") {}

    void SelfAlpha::proc(cv::Mat &frame, Args &args) {
        for(int z = 0; z < frame.rows; ++z) {
            for(int i = 0; i < frame.cols; ++i) {
                
                cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
                for(int j = 0; j < 3; ++j)
                    pixel[j] = wrap_cast(pixel[j] * args.alpha);
                
            }
        }
        args.move_in_out();
    }
}
