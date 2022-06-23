#include"ac-filterlist.hpp"
#include<iostream>


class Filter1_FillRect : public ac::FilterObj {
public:
    Filter1_FillRect(int xx = 0, int yy = 0) : x{0}, y{0} {
        init();
    }
    
    ~Filter1_FillRect() {
        cleanup();
    }
    
    void init() override {
        std::cout << "Filter1 init...\n";
    }
    
    void update(cv::Mat &frame) override {
        for(int z = y; z < frame.rows; ++z) {
            for(int i = x; i < frame.cols; ++i) {
                frame.at<cv::Vec3b>(z, i) = color;
            }
        }
    }
    
    void cleanup() override {
        std::cout << "Filter1 cleanup...\n";
    }
private:
    int x = 0, y = 0;
    cv::Vec3b color{0, 0, 0};
};

class Filter2_FillHalfGreen : public ac::FilterObj {
public:
    
    Filter2_FillHalfGreen() {
        init();
    }
    
    ~Filter2_FillHalfGreen() {
        cleanup();
    }
    
    void init() override {
        std::cout << "Filter2 init...\n";
    }
    
    
    void cleanup() override {
        std::cout << "Filter2 cleanup...\n";
    }
    
    void update(cv::Mat &frame) override {
        for(int z = frame.rows/2; z < frame.rows; ++z) {
            for(int i = frame.cols/2; i < frame.cols; ++i) {
                frame.at<cv::Vec3b>(z, i) = cv::Vec3b(0, 255, 0);
            }
        }
    }
    private:
};


int main(int argc, char **argv) {
    if(argc == 2) {
        ac::FilterList list;
        list.add(new Filter1_FillRect());
        list.add(new Filter2_FillHalfGreen());
        cv::Mat m = cv::imread(argv[1]);
        if(!m.empty())
            list.exec(m);
        cv::imwrite("output.png", m);
        std::cout << "output: output.png\n";
    } else
        std::cerr << "Error use: " << argv[0] << " image_path\n";
    
    return 0;
}
