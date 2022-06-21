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
    Filter1 filter1;
    Filter2 filter2;
    ac::FilterList list;
    list.add(&filter1);
    list.add(&filter2);
    cv::Mat m = cv::imread("test.png");
    if(!m.empty())
    list.exec(m);
    return 0;
}
