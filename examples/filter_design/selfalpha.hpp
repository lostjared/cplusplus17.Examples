#ifndef _SELF_ALPHA_H_
#define _SELF_ALPHA_H_

#include"ac_filter.hpp"

namespace ac {

    class SelfAlpha : public AC_Filter {
    public:
        SelfAlpha();
    protected:
      void proc(cv::Mat &frame, Args &args) override;
    
    };

}

#endif

