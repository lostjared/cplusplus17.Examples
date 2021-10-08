#include<opencv2/opencv.hpp>
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<filesystem>

#include"cmd-switch.hpp"

void processFile(std::string inputFile, std::string outputType,bool res, int width, int height, std::string output_path);

int main(int argc, char **argv) {
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string input_file;
        argz.require("--input", input_file, "input file");
        std::string output_type;
        argz.require("--output", output_type, "output type");
        std::string resolution;
        bool res=argz.extract("--res", resolution);
        std::string path;
        argz.extract("--path", path);
        if(res) {
            auto pos = resolution.find("x");
            if(pos == std::string::npos) {
                std::cerr << "Invalid resolution string use WidthxHeight\n";
                return 0;
            }
            std::string left=resolution.substr(0, pos);
            std::string right=resolution.substr(pos+1, resolution.length());
            processFile(input_file, output_type, res, atoi(left.c_str()), atoi(right.c_str()), path);
        } else {
            processFile(input_file, output_type, false, 0, 0, path);
        }
    }
    catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
    }
    
    return 0;
}

void processFile(std::string inputFile, std::string outputType,bool res, int width, int height, std::string output_path) {
    
    std::filesystem::path file_path{inputFile};
       
    if(is_directory(file_path)) {
        std::cerr << "Error input file is directory...\n";
        exit(EXIT_FAILURE);
    }
    if(!exists(file_path)) {
        std::cerr << "Error input file: " << file_path.string() << " does not exisit..\n";
        exit(EXIT_FAILURE);
    }
    
    std::fstream file;
    file.open(inputFile, std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error could not open input file..\n";
        exit(EXIT_FAILURE);
    }
    
    std::filesystem::path output_p;
    
    if(output_path != "") {
        if(std::filesystem::create_directories(output_path)) {
            std::cout << "created: " << output_path << "\n";
        }
        output_p = std::filesystem::path(output_path);
        output_path += "/";
    } else {
        output_p = std::filesystem::path(".");
    }
    
    while(!file.eof()) {
        std::string in_file;
        std::getline(file, in_file);
        if(file) {
            std::filesystem::path file_p{in_file};
            if(is_directory(file_p) || !exists(file_p))
                continue;
            
            auto pos = in_file.rfind(".");
            if(pos == std::string::npos) continue;
            std::string left = in_file.substr(0, pos);
            
            auto pos_fname = left.rfind("/");
            if(pos_fname != std::string::npos)
                left = left.substr(pos_fname+1, left.length());

            cv::Mat img = cv::imread(in_file);
             if(!img.empty()) {
                if(res == true) {
                    std::ostringstream stream;
                    cv::Mat copy;
                    stream << output_p.string() << "/" << left << "_" << width << "x" << height << "." << outputType;
                    cv::resize(img, copy, cv::Size(width, height));
                    if(!cv::imwrite(stream.str(), copy))
                        std::cerr << "error could not write: " << stream.str() << "\n";
                    else
                        std::cout << "wrote: " << stream.str() << "\n";
                } else {
                    std::ostringstream stream;
                    stream << output_p.string() << "/" << left << "." << outputType;
                    if(!cv::imwrite(stream.str(), img))
                        std::cerr << "error could not write: " << stream.str() << "\n";
                    else
                        std::cout << "wrote: " << stream.str() << "\n";
                }
                
            } else {
                std::cerr << "Error reading image: " << in_file << "\n";
            }
        }
    }
}
