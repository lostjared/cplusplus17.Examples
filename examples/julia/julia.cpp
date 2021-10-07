
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

bool splitDoublePair(const std::string &value, const std::string &sep, double &val1, double &val2) {
    auto pos = value.find(sep);
    if(pos == std::string::npos)
        return false;
    std::string left = value.substr(0, pos);
    std::string right = value.substr(pos+1, value.length()-pos);
    val1 = atof(left.c_str());
    val2 = atof(right.c_str());
    return true;
}

bool splitIntegerPair(const std::string &value, const std::string &sep, int &val1, int &val2) {
    auto pos = value.find(sep);
    if(pos == std::string::npos)
        return false;
    std::string left = value.substr(0, pos);
    std::string right = value.substr(pos+1, value.length()-pos);
    val1 = atoi(left.c_str());
    val2 = atoi(right.c_str());
    return true;
}

bool splitTuple(const std::string &value, const std::string &sep, cv::Vec3b &t) {
    auto pos = value.find(sep);
    if(pos == std::string::npos)
        return false;
    std::string left = value.substr(0, pos);
    std::string right = value.substr(pos+1, value.length()-pos);
    t[0] = atoi(left.c_str());
    auto pos1 = right.find(",");
    if(pos == std::string::npos)
        return false;
    std::string leftof = right.substr(0, pos1);
    std::string rightof = right.substr(pos1+1, right.length()-pos1);
    t[1] = atoi(leftof.c_str());
    t[2] = atoi(rightof.c_str());
    return true;
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
    if(argc != 7) {
        std::cerr << "Error invalid arguments..\n";
        std::cerr << "arguments:\n julia output.png WidthxHeight iterations paramA,paramB red,green,blue thread_count\n";
        exit(EXIT_FAILURE);
    }
    std::string filename = argv[1];
    int width = 0;
    int height = 0;
    if(!splitIntegerPair(argv[2], "x", width, height)) {
        std::cerr << "error invalid resolution use WidthxHeight\n";
        exit(EXIT_FAILURE);
    }
    int iterations = atoi(argv[3]);
    
    double paramA = 0, paramB = 0;
    if(!splitDoublePair(argv[4], ",", paramA, paramB)) {
        std::cerr << "error invalid complex pair: use number, number\n";
        exit(EXIT_FAILURE);
    }
    cv::Vec3b rgb;
    if(!splitTuple(argv[5], ",", rgb)) {
        std::cerr << "invalid color tuple..\n use red,green,blue.\n";
        exit(EXIT_FAILURE);
    }
    int tc = atoi(argv[6]);
    
    if(width <= 32 || height <= 32 || iterations <= 0 || tc < 1) {
        std::cerr << "invalid arguments...\n";
        exit(EXIT_FAILURE);
    }
    
    if(iterations > 0)
        frac::MAX_ITER = iterations;
    
    std::cout << "creating: " << filename << " " << width << "x" << height << " threads: " << tc <<  " RGB(" << int(rgb[0]) << "," << int(rgb[1]) << "," << int(rgb[2]) << ") - " << "(" << paramA << "," << paramB << ")\n";
    
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
