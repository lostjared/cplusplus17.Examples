#ifndef __STATIC_IF_HPP_
#define __STATIC_IF_HPP_

namespace st {

    class staticIF {
    public:
        template<typename F1, typename F2>
        staticIF(F1 in, F2 out) {
            in();
            release = out;
        }
        
        ~staticIF() {
            release();
        }
        
    protected:
        //F2 free;
        void (*release)();
    };
}


#endif

