
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
        virtual ~FilterObject() {}
        void setID(const std::string &s);
        virtual void operator()(/*cv::Mat &frame*/) = 0;
        virtual void reset() = 0;
    protected:
        double alpha;
        std::string id;
        //MatrixCollection
        //cv::Mat
    private:
    };
    
    class SelfAlphaBlend : public FilterObject {
    public:
        SelfAlphaBlend();
        void operator()() override;
        void reset() override;
    };
    
    class SelfScale : public FilterObject {
    public:
        SelfScale();
        void operator()(/*cv::Mat &frame*/) override;
        void reset() override;
    };
}

#endif

