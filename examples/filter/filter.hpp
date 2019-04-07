
#ifndef __FILTER_TEST__H__
#define __FILTER_TEST__H__

#include<iostream>
#include<string>

namespace ac {

    class FilterObject {
    public:
        FilterObject();
        FilterObject(const std::string &s);
        FilterObject(const FilterObject &fo);
        FilterObject &operator=(const FilterObject &fo);
        void setID(const std::string &s);
        virtual void operator()(/*cv::Mat &frame*/) = 0;
    protected:
        double alpha;
        std::string id;
        //MatriCollection
    };
    
    class SelfAlphaBlend : public FilterObject {
    public:
        SelfAlphaBlend();
        void operator()(/*cv::Mat &frame*/);
    };
}

#endif

