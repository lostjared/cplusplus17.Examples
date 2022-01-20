#ifndef _AC_FILTER_H__
#define _AC_FILTER_H__

#include<string>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
#include<unordered_map>

namespace ac {


    unsigned char wrap_cast(double d);

    class AC_Filter {
    public:
        AC_Filter(const std::string &name);
        virtual ~AC_Filter() = default;
        void exec(cv::Mat &frame);
        std::string get_name() const;
        void setalpha(double d);
    protected:
         struct Args {
            //MatrixCollection<32> collection;
            double alpha = 1.0;
            bool dir = true;
            void move_in_out();
        };
        std::string name;
        static Args args;
        virtual void proc(cv::Mat &frame, Args &args) = 0;
    };

    extern std::vector<AC_Filter *> filters;
    extern std::unordered_map<std::string, AC_Filter *> map_filter;
}
#endif


