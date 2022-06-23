#include"ac-filterlist.hpp"
#include<iostream>


class Filter1 : public ac::FilterObj {
public:
    Filter1() {
        init();
    }
    
    ~Filter1() {
        cleanup();
    }
    
    void init() override {
        std::cout << "Filter1 init...\n";
    }
    
    void update(cv::Mat &frame) override {
        std::cout << "x: " << x << " y: " << y << "\n";
    }
    
    void cleanup() override {
        std::cout << "Filter1 cleanup...\n";
    }
private:
    int x = 10, y = 20;
};

class Filter2 : public ac::FilterObj {
public:
    
    Filter2() {
        init();
    }
    
    ~Filter2() {
        cleanup();
    }
    
    void init() override {
        std::cout << "Filter2 init...\n";
    }
    
    
    void cleanup() override {
        std::cout << "Filter2 cleanup...\n";
    }
    
    void update(cv::Mat &frame) override {
        std::cout << "z: " << z << " q: " << q << "\n";
    }
    private:
    int z = 50, q = 100;
};


int main(int argc, char **argv) {
    if(argc == 2) {
        ac::FilterList list;
        list.add(new Filter1());
        list.add(new Filter2());
        cv::Mat m = cv::imread(argv[1]);
        if(!m.empty())
            list.exec(m);
    } else
        std::cerr << "Error use: " << argv[0] << " image_path\n";
    
    return 0;
}
