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

    void FilterList::call(int n, cv::Mat &frame) {
        if(n >= 0 && n < objects.size())
            objects[n]->update(frame);
    }


    void FilterList::clear() {
        if(!objects.empty())
            objects.erase(objects.begin(), objects.end());
    }

    void FilterList::rmv(int n) {
        if(n >= 0 && n < objects.size())
            objects.erase(objects.begin()+n);
    }

    
    void FilterList::pop() {
        objects.pop_back();
    }


}
