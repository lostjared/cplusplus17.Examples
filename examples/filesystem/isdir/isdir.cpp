#include<iostream>
#include<filesystem>

int main(int argc, char **argv) {
    if(argc == 1) {
        std::cerr << "Error use " << argv[0] << " path.\n";
        return 1;
    }
    std::filesystem::path file_path{argv[1]};
    if(is_directory(file_path)) {
        std::cout << file_path.string() << " is a directory.\n";
    } else {
        std::cout << file_path.string() << " is not a directory.\n";
    }
    return 0;
}
                            
