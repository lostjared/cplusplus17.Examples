// Arguments take the form of
// --switch=value
// --file=input-filename
// --filter=index

#include<iostream>
#include"ac.h"
#include"cmd-switch.hpp"

int main(int argc, char **argv) {
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string filename;
        std::string filter;
        argz.require("--file", filename, "input video file");
        argz.require("--filter", filter, "filter index");
        
        ac::init();
        cv::VideoCapture cap(filename);
        if(!cap.isOpened()) {
            std::cerr << "Could not open vidoe file: "<< filename << "\n";
            exit(EXIT_FAILURE);
        }
        
        bool active = true;
        cv::namedWindow("acidcam");
        int filter_index = atoi(filter.c_str());
        
        if(filter_index < 0 || filter_index > ac::getFilterCount()-1) {
            std::cerr << "Error: invalid filter Index..\n";
            exit(EXIT_FAILURE);
        }
        
        while(active) {
            cv::Mat frame;
            if(cap.read(frame)) {
                ac::CallFilter(filter_index, frame);
                cv::imshow("acidcam", frame);
                int key = cv::waitKey(10);
                if(key == 27) exit(EXIT_SUCCESS);
            } else break;
        }
    } catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
