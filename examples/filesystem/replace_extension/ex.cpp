#include<iostream>
#include<filesystem>
#include<string>
#include<cstdlib>

std::string build_filename(const std::string &filename, const std::string &output_path,const std::string &ext) {
    std::filesystem::path p{filename};
    p.replace_extension(ext);
    std::filesystem::path output_p{output_path};
    output_p.append(p.filename().string());
    return output_p.string();
}

int main(int argc, char **argv) {
    if(argc == 1) {
        std::cerr << "Error use " << argv[0] << " filename path extension.\n";
        return EXIT_SUCCESS;
    }
    if(argc == 4) {
        std::cout << "final path: " << build_filename(argv[1], argv[2], argv[3]) << "\n";
    } else {
        std::cerr << "invalid arguments..\n";
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
