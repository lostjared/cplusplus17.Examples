#include<opencv2/opencv.hpp>
#include<iostream>

void splitCamera(cv::Mat &frame, cv::Mat frame2) {
    cv::Mat img;
    cv::resize(frame, img, cv::Size(frame.cols/2, frame.rows));
    cv::Mat copy;
    cv::resize(frame2, copy, cv::Size(frame.cols/2, frame.rows));
    for(int z = 0; z < frame.rows; ++z) {
        int x = 0;
        for(int i = frame.cols/2; i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            cv::Vec3b pix = copy.at<cv::Vec3b>(z, x);
            ++x;
            pixel = pix;
        }
        for(int i = 0; i < frame.cols/2; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            cv::Vec3b pix = img.at<cv::Vec3b>(z, i);
            pixel = pix;
        }
    }
}

int main(int argc, char **argv) {
    
    if(argc != 3) {
        std::cerr << "Error requires two arguments:\n cam1_index cam2_index \n";
        exit(EXIT_FAILURE);
        return 0;
    }

    cv::VideoCapture cap(atoi(argv[1]));
    if(!cap.isOpened()) {
        std::cerr << "Could not open capture device 1..\n";
        exit(EXIT_FAILURE);
    }
    cv::VideoCapture cap2(atoi(argv[2]));
    if(!cap2.isOpened()) {
        std::cerr << "Could not open capture device 2..\n";
        exit(EXIT_FAILURE);
    }

    bool active = true;
    cv::namedWindow("cv-stereo-cam");
    while(active) {
        cv::Mat m;
        cv::Mat m1;
        if(cap.read(m) && cap2.read(m1)) {
            splitCamera(m, m1);
            cv::imshow("cv-stereo-cam", m);
            if(cv::waitKey(10) == 27)
                exit(EXIT_SUCCESS);
        } else {
            std::cerr << "close...\n";
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}
