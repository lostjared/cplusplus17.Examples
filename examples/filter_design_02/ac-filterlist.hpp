#ifndef __FILTER_OBJ__H__
#define __FILTER_OBJ__H__

#include "ac.h"
#include<iostream>
#include<deque>
#include<memory>

namespace ac {


    class FilterObj {
    public:
        virtual ~FilterObj() = default;
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
        std::deque<std::unique_ptr<FilterObj>> objects;
    };

}

#endif

