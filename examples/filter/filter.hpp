
#ifndef __FILTER_TEST__H__
#define __FILTER_TEST__H__

#include<iostream>
#include<string>

namespace ac {

    class FilterObject {
    public:
        FilterObject();
        FilterObject(const FilterObject &fo);
        FilterObject &operator=(const FilterObject &fo);
    private:
        //cv::Mat frame;
        double alpha;
        //MatriCollection
    };
    
}

#endif

