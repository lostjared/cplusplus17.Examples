#include "ac-filterlist.hpp"

namespace ac {

    FilterList::~FilterList() {
    
    }

    void FilterList::add(FilterObj *obj) {
        objects.push_back(obj);
    }
    
    void FilterList::exec(cv::Mat &frame) {
        for(auto &i : objects)
            i->update(frame);
    }

}
