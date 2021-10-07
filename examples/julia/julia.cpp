
#include<opencv2/opencv.hpp>
#include<iostream>
#include<complex>
#include<string>
#include<thread>
#include<vector>

namespace frac {
    int MAX_ITER=80;
    void DrawFractal(cv::Mat &frame, int thread_count, cv::Vec3b rgb, double paramA, double paramB);
    int julia(const std::complex<double> &c, std::complex<double> zval);
}


int frac::julia(const std::complex<double> &c, std::complex<double> z) {
    int n = 0;
    while(std::abs(z) <= 2 && n < MAX_ITER) {
        z = z*z+c;
        n ++;
    }
    return n + 1 - std::log(std::log2(std::abs(z)));
}

template<typename F>
void UseMultipleThreads(cv::Mat &frame, int cores, F func) {
    int size = frame.rows/cores;
    std::vector<std::thread> values;
    for(int i = 0; i < cores; ++i) {
        values.push_back(std::thread(func, &frame, i*size, frame.cols, size));
    }
    for(unsigned int i = 0; i < values.size(); ++i) {
        values[i].join();
    }
}


void frac::DrawFractal(cv::Mat &frame, int thread_count, cv::Vec3b rgb, double paramA, double paramB) {
    int width=frame.cols, height=frame.rows;
    double start = -2.0;
    double end = 2;
    double im_start = -1.0;
    double im_end = 1;
    static auto callback = [&](cv::Mat *frame, int offset, int cols, int size) {
        for(int z = offset; z <  offset+size; ++z) {
            for(int i = 0; i < cols; ++i) {
                cv::Vec3b &pixel = frame->at<cv::Vec3b>(z, i);
                double w = (double(i)/double(width));
                double h = (double(z)/double(height));
                std::complex<double> zval(start + w * (end - start), im_start + h * (im_end - im_start));
                std::complex<double> c(paramA, paramB);
                int n = julia(c, zval);
                unsigned char color = static_cast<unsigned char>(255-(n * 255 / MAX_ITER));
                
                unsigned char red = 50, green = 100, blue = 150;
                
                pixel[0] = color + 255-(n/1+rgb[0]);
                pixel[1] = color + 255-(n/1+rgb[1]);
                pixel[2] = color + 255-(n/1+rgb[2]);
            }
        }
    };
    UseMultipleThreads(frame, thread_count, callback);
}

int main(int argc, char **argv) {
    
    if(argc != 11) {
        std::cerr << "Error invalid arguments..\n";
        std::cerr << "arguments:\n julia output.png width height iterations paramA paramB red green blue thread_count\n";
        exit(EXIT_FAILURE);
    }
    
 
    std::string filename = argv[1];
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    int iterations = atoi(argv[4]);
    double paramA = atof(argv[5]);
    double paramB = atof(argv[6]);
    cv::Vec3b rgb;
    rgb[0] = atoi(argv[7]);
    rgb[1] = atoi(argv[8]);
    rgb[2] = atoi(argv[9]);
    int tc = atoi(argv[10]);
    
    if(width <= 32 || height <= 32 || iterations <= 0 || tc < 1) {
        std::cerr << "invalid arguments...\n";
        exit(EXIT_FAILURE);
    }
    
    if(iterations > 0)
        frac::MAX_ITER = iterations;
    
    std::cout << "creating: " << filename << " " << width << "x" << height << " threads: " << tc << "\n";
    
    cv::Mat m;
    m.create(cv::Size(width, height), CV_8UC3);
    frac::DrawFractal(m, tc, rgb, paramA, paramB);
    if(!cv::imwrite(filename, m)) {
        std::cerr << "could not write file..\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "wrote file: " << filename << "\n";
    return 0;
}
