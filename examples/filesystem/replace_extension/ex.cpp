#include<iostream>
#include<filesystem>
#include<string>

std::string build_filename(const std::string &filename, const std::string &output_path) {
    std::filesystem::path p{filename};
    p.replace_extension(".png");
    std::filesystem::path output_p{output_path};
    output_p.append(p.filename().string());
    return output_p.string();
}

int main(int argc, char **argv) {
    if(argc == 1) {
        std::cerr << "Error use " << argv[0] << " path.\n";
        return 1;
    }
    if(argc == 3) {
        std::cout << "final path: " << build_filename(argv[1], argv[2]) << "\n";
    } else {
        std::cerr << "invalid arguments..\n";
        return 1;
    }
    return 0;
}
