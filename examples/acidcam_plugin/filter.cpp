// simple filter plugin example
#include<iostream>
#include<opencv2/opencv.hpp>

extern "C" void filter(cv::Mat &frame) {
    static float alpha = 1.0;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++z) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            for(int q = 0; q < 3; ++q) {
                pixel[q] = static_cast<unsigned char>(pixel[q] * alpha);
                
            }
        }
    }
    alpha += 0.01;
    if(alpha > 4.0)
        alpha = 1.0;
}
