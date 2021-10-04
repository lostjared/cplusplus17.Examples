#include<iostream>
#include<cstdlib>
#include"acidcam/ac.h"
#include"cmd-switch.hpp"

int main(int argc, char **argv) {

    std::string input_file, output_file, filter, level;
    bool continue_image = false;
    try {
        cmd::ArgumentList<std::string> argz(argc, argv,
        "ac-tool\n use \n --input=[file input]\n --output=[file output]\n --filter=[filter ]\n --level=[filter depth]\n --continue (chain calls)\n --list (list filters)\n");
        
        if(argz.check("--list") == true) {
            ac::init();
            for(int i = 0; i < ac::solo_filter.size(); ++i) {
                std::cout << ac::solo_filter[i] << "\n";
            }
            exit(EXIT_SUCCESS);
        }
        
        argz.require("--input", input_file, "input file");
        argz.require("--output", output_file, "output file");
        argz.require("--filter", filter, "filter");
        argz.require("--level", level, "level");
        continue_image = argz.check("--continue");
        
    } catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    } catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
  
  
    ac::init();

    if(std::find(ac::solo_filter.begin(), ac::solo_filter.end(), filter) == ac::solo_filter.end()) {
        std::cerr << "ac-tool: Filter not found.\n";
        exit(EXIT_FAILURE);
    }
    
    cv::Mat m_in;
    m_in = cv::imread(input_file);
    if(m_in.empty()) {
        std::cerr << "Error could not open file..\n";
        exit(EXIT_FAILURE);
    }
    cv::Mat copy = m_in.clone();
    int level_in = atoi(level.c_str());
    if(level_in >= 1 && level_in < 128) {
        for(int i = 0; i < level_in; ++i) {
            if(continue_image == false)
                copy = m_in.clone();
            ac::CallFilter(filter, copy);
        }
        cv::imwrite(output_file, copy);
        std::cout << "ac-tool: Wrote file " << output_file << "\n";
    }
    return EXIT_SUCCESS;
}
