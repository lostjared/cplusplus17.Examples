#ifndef _DMD_H__X
#define _DMD_H__X

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

class Diamond {
public:
    Diamond() = delete;
    Diamond(const Diamond &d) = delete;
    Diamond(Diamond &&d) {
        files = std::move(d.files);
        index = d.index;
        file = std::move(d.file);
    }
    Diamond(int argc, char **argv) {
        if(argc >= 2) {
            for(unsigned int i = 1; i < argc; ++i) {
                files.push_back(argv[i]);
            }
        } else {
            index = 0;
            return;
        }
        reset();
    }
    Diamond &operator=(const Diamond &d) = delete;
    Diamond &operator=(Diamond &&d) {
        files = std::move(d.files);
        index = d.index;
        file = std::move(d.file);
        return *this;
    }
    bool next(std::string &line) {
        
        if(files.size() == 0) {
            std::getline(std::cin, line);
            if(std::cin)
                return true;
            else
                return false;
        }
        
        std::getline(file, line);
        if(file) {
            return true;
        } else {
            ++index;
             if(index < files.size()) {
                file.close();
                file.open(files[index], std::ios::in);
                if(!file.is_open()) {
                    std::cerr << "Error could not open file: " << files[index] << "...\n";
                    return next(line);
                }
                std::getline(file, line);
                return true;
             }
        }
        return false;
    }
    
    void reset() {
        if(file.is_open())
            file.close();
        index = 0;
        file.open(files[index], std::ios::in);
        if(!file.is_open()) {
            std::cerr << "Error could not open file: " << files[index] << "..\n";
        }
    }
    
protected:
    std::vector<std::string> files;
    unsigned int index;
    std::fstream file;
};


#endif

