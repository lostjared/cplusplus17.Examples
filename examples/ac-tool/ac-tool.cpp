#include<iostream>
#include"acidcam/ac.h"
#include"cmd-switch.hpp"


int main(int argc, char **argv) {
    std::string input_file, output_file, filter, level;
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        argz.require("--input", input_file, "input file");
        argz.require("--output", output_file, "output file");
        argz.require("--filter", filter, "filter");
        argz.require("--level", level, "level");
    } catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    } catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    
    ac::init();
    
    cv::Mat m_in;
    m_in = cv::imread(input_file);
    if(m_in.empty()) {
        std::cerr << "Error could not open file..\n";
        exit(EXIT_FAILURE);
    }
    cv::Mat copy;
    
    int level_in = atoi(level.c_str());
    if(level_in >= 1 && level_in < 64) {
        for(int i = 0; i < level_in; ++i) {
            copy = m_in.clone();
            ac::CallFilter(filter, copy);
        }
        cv::imwrite(output_file, copy);
        std::cout << "ac-tool: Wrote file " << output_file << "\n";
    }
    return 0;
}
