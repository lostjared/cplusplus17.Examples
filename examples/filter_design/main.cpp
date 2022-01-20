#include"ac_filter.hpp"
#include"selfalpha.hpp"
#include<iostream>

ac::SelfAlpha alpha;

int main(int argc, char **argv) {
    if(argc <= 3) {
        for(size_t i = 0; i < ac::filters.size(); ++i) {
            std::cout << i << ": " << ac::filters[i]->get_name() << "\n";
        }
        exit(0);
    }
    else if(argc == 4){
        cv::Mat img = cv::imread(argv[1]);
        if(img.empty()) {
            std::cerr << "Error loading: " << argv[1] << "\n";
            exit(EXIT_FAILURE);
        }
        size_t index = atoi(argv[2]);
        double d = atof(argv[3]);
        if(index >= 0 && index < ac::filters.size()) {
            ac::filters[index]->setalpha(d);
            ac::filters[index]->exec(img);
        } else {
            std::cerr << "Error invalid index...\n";
            exit(EXIT_FAILURE);
        }
        cv::imwrite("output.png", img);
        std::cout << "wrote: output.png\n";
    }
    return 0;
}
