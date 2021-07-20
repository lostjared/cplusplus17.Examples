#include<iostream>
#include<filesystem>
#include<string>
#include<cstdlib>

int main(int argc, char **argv) {
    if(argc == 1) {
        std::cerr << "Error requires one argument filename..\n";
        exit(EXIT_SUCCESS);
    }
    std::filesystem::path file_path{argv[1]};
    std::cout << "path components: \n";
    for(auto &i : file_path) {
        std::cout << i.string() << "\n";
    }
    // or
    for(auto p = file_path.begin(); p != file_path.end(); ++p) {
        std::cout << p->string() << "\n";
    }
    
    file_path.append("New_Dir");
    file_path.concat("1");
    std::cout << file_path.string() << "\n";
    
    return EXIT_SUCCESS;
}
