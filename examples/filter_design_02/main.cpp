#include"ac-filterlist.hpp"
#include<iostream>


class Filter1 : public ac::FilterObj {
public:
    void init() override {
        
    }
    
    void update(cv::Mat &frame) override {
        std::cout << "x: " << x << " y: " << y << "\n";
    }
    
    void cleanup() override {
        
    }
private:
    int x = 10, y = 20;
};

class Filter2 : public ac::FilterObj {
    
    void init() override {
        
    }
    
    void update(cv::Mat &frame) override {
        std::cout << "z: " << z << " q: " << q << "\n";
    }
    
    void cleanup() override {
        
    }
private:
    int z = 50, q = 100;
};


int main(int argc, char **argv) {
    if(argc == 2) {
        Filter1 filter1;
        Filter2 filter2;
        ac::FilterList list;
        list.add(&filter1);
        list.add(&filter2);
        cv::Mat m = cv::imread(argv[1]);
        if(!m.empty())
            list.exec(m);
    } else
        std::cerr << "Error use: " << argv[0] << " image_path\n";
    
    return 0;
}
