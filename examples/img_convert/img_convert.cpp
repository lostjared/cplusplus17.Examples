#include<opencv2/opencv.hpp>
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<algorithm>
#include<sstream>
#include"cmd-switch.hpp"

void processFile(std::string inputFile, std::string outputType,bool res, int width, int height);

int main(int argc, char **argv) {
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string input_file;
        argz.require("--input", input_file, "input file");
        std::string output_type;
        argz.require("--output", output_type, "output type");
        std::string resolution;
        bool res=argz.extract("--res", resolution);
        if(res) {
            auto pos = resolution.find("x");
            if(pos == std::string::npos) {
                std::cerr << "Invalid resolution string use WidthxHeight\n";
                return 0;
            }
            std::string left=resolution.substr(0, pos);
            std::string right=resolution.substr(pos+1, resolution.length());
            processFile(input_file, output_type, res, atoi(left.c_str()), atoi(right.c_str()));
        } else {
            processFile(input_file, output_type, false, 0, 0);
        }
    }
    catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    
    return 0;
}

void processFile(std::string inputFile, std::string outputType,bool res, int width, int height) {
    std::fstream file;
    file.open(inputFile, std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error could not open input file..\n";
        exit(EXIT_FAILURE);
    }
    while(!file.eof()) {
        std::string in_file;
        std::getline(file, in_file);
        if(file) {
            auto pos = in_file.rfind(".");
            if(pos == std::string::npos) continue;
            std::string left = in_file.substr(0, pos);
            cv::Mat img = cv::imread(in_file);
             if(!img.empty()) {
                if(res == true) {
                    std::ostringstream stream;
                    cv::Mat copy;
                    stream << left << "_" << width << "x" << height << "." << outputType;
                    cv::resize(img, copy, cv::Size(width, height));
                    cv::imwrite(stream.str(), copy);
                    std::cout << "wrote: " << stream.str() << "\n";
                } else {
                    std::ostringstream stream;
                    stream << left << "." << outputType;
                    cv::imwrite(stream.str(), img);
                    std::cout << "wrote: " << stream.str() << "\n";
                }
                
            } else {
                std::cerr << "Error reading image: " << in_file << "\n";
            }
        }
    }
}

