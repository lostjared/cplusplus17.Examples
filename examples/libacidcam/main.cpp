#include<iostream>
#include"ac.h"

int main(int argc, char **argv) {
    ac::init();
    if(argc != 3) {
        std::cerr << "Requires two argument..\nVideo file/filter..\n";
        exit(EXIT_FAILURE);
    }
    cv::VideoCapture cap(argv[1]);
    if(!cap.isOpened()) {
        std::cerr << "Could not open vidoe file: "<< argv[1] << "\n";
    }
    
    bool active = true;
    cv::namedWindow("acidcam");
    while(active) {
        cv::Mat frame;
        if(cap.read(frame)) {
            ac::CallFilter(atoi(argv[2]), frame);
            cv::imshow("acidcam", frame);
            int key = cv::waitKey(10);
            if(key == 27) exit(EXIT_SUCCESS);
        } else break;
    }
    return 0;
}
