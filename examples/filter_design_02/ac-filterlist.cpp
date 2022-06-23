#include "ac-filterlist.hpp"

namespace ac {

    FilterList::~FilterList() {
    
    }

    
    FilterList::FilterList(FilterList &&l) : objects{std::move(l.objects)} {
    
    }


    FilterList &FilterList::operator=(FilterList &&l) {
        objects = std::move(l.objects);
        return *this;
    }


    void FilterList::add(FilterObj *obj) {
        objects.push_back(std::unique_ptr<FilterObj>(obj));
    }
    
    void FilterList::exec(cv::Mat &frame) {
        for(auto &i : objects)
            i->update(frame);
    }

}
