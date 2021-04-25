/*

 Practice
 Use
 
 ./shell-cmd path "command %f" .file_extension
 ex:
 ./shell-cmd . "cat %f" .txt
 
 to execute command for each file type within directory/subdirectory
 just written to practice
  
*/

#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sstream>
#include<cstdlib>

std::string replace_string(std::string orig, std::string with, std::string rep) {
    auto pos = orig.find(with);
    if(pos == std::string::npos) {
        return orig;
    }
    std::string left;
    left = orig.substr(0, pos);
    std::string right;
    right = orig.substr(pos+with.length(), orig.length());

    std::string f;
    f = left+rep+right;
    return replace_string(f,with,rep);
}

void add_directory(std::string path, std::vector<std::string> &files, std::string type) {
    DIR *dir = opendir(path.c_str());
    if(dir == NULL) {
        std::cerr << "Error could not open directory: " << path << "\n";
        exit(EXIT_FAILURE);
        return;
    }
    dirent *file_info;
    while( (file_info = readdir(dir)) != 0 ) {
        std::string f_info = file_info->d_name;
        if(f_info == "." || f_info == "..")  continue;
        std::string fullpath=path+"/"+f_info;
        struct stat s;
        
        lstat(fullpath.c_str(), &s);
        if(S_ISDIR(s.st_mode)) {
            if(f_info.length()>0 && f_info[0] != '.')
                add_directory(path+"/"+f_info, files, type);

            continue;
        }
        if(f_info.length()>0 && f_info[0] != '.') {
            if(fullpath.find(type) != std::string::npos) {
                files.push_back(fullpath);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char **argv) {
    
    if(argc != 4) {
        std::cerr << "Error: requires three arguments..\n";
        std::cerr << "use: \nshell-cmd: path command %f filetype\n";
        exit(EXIT_FAILURE);
    }
    
    std::string input = argv[2];
    if(input.find("%f") == std::string::npos) {
        std::cerr << "requires %f for filename..\n";
        exit(EXIT_FAILURE);
    }
    
    std::vector<std::string> cur_dir;
    add_directory(argv[1], cur_dir, argv[3]);
    for(unsigned int i = 0; i < cur_dir.size(); ++i) {
        std::string text =  cur_dir[i];
        std::string cmd = argv[2];
        std::string r = replace_string(cmd, "%f", text);
        std::cout << r << "\n";
        system(r.c_str());
    }
    return 0;
}
