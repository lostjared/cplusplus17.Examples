#include<iostream>
#include<filesystem>
#include<string>

int main(int argc, char **argv) {
    
    if(argc == 1) {
        std::cerr << "Use " << argv[0] << " file\n to print file size\n";
        return 0;
    }
    
    std::filesystem::path file_path{argv[1]};
    if(!is_directory(file_path)) {
        std::cout << "file: " << file_path.string() << " is " << file_size(file_path) << " bytes.\n";
    } else {
        std::cout << "is a directory..\n";
        return 1;
    }
    return 0;
}
