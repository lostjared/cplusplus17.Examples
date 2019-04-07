#include "filter.hpp"

namespace ac {
    
    // initalize
    FilterObject::FilterObject() : alpha(0) {
        
    }
    
    FilterObject::FilterObject(const FilterObject &fo) {
        this->operator=(fo);
    }
    FilterObject &FilterObject::operator=(const FilterObject &fo) {
        // copy data
        // collection = fo.collection
        alpha = fo.alpha;
        return *this;
    }
    
}
