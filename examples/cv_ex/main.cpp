#include<opencv2/opencv.hpp>
#include<iostream>
int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cerr << "Error requires one argument capture device index..\n";
        exit(EXIT_FAILURE);
        return 0;
    }
    
    cv::VideoCapture cap(atoi(argv[1]));
    if(!cap.isOpened()) {
        std::cerr << "Could not open capture device..\n";
        exit(EXIT_FAILURE);
    }
    bool active = true;
    cv::namedWindow("cv");
    while(active) {
        cv::Mat m;
        if(cap.read(m)) {
            cv::imshow("cv", m);
            if(cv::waitKey(10) == 27)
                exit(EXIT_SUCCESS);
        }
    }
    return EXIT_SUCCESS;
}
