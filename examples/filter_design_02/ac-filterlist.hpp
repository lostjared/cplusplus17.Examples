#ifndef __FILTER_OBJ__H__
#define __FILTER_OBJ__H__

#include "ac.h"
#include "ac-filterobj.hpp"
#include<iostream>
#include<deque>

namespace flist {


    class FilterObj {
    public:
        virtual void init() = 0;
        virtual void update(cv::Mat &frame) = 0;
        virtual void cleanup() = 0;
    };


    class FilterList {
    public:
        FilterList() = default;
        ~FilterList();
        void add(FilterObj *obj);
        void exec(cv::Mat &frame);
    private:
        std::deque<FilterObj *> objects;
    };

}

#endif

