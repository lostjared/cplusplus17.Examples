/*

 for Practice
 Use
 
 ./shell-cmd path "command %f" regex_search_pattern
 ex:
 ./shell-cmd . "cat %f" .txt
 
 actual example extract all archives:
 
 $ shell-cmd . "7z e %f" .7z
 
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
#include<sys/wait.h>
#include<signal.h>
#include<sstream>
#include<cstdlib>
#include<regex>

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
            std::regex ex(type);
            if(std::regex_search(fullpath, ex)) {
                files.push_back(fullpath);
            }
        }
    }
    closedir(dir);
}

int System(const std::string &command) {
    sigset_t bmask, omask;
    struct sigaction sa_ignore, sa_oquit, sa_origint, sa_default;
    pid_t id;
    int status, serrno;
    
    if(command == "") return System(":") == 0;
    
    sigemptyset(&bmask);
    sigaddset(&bmask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &bmask, &omask);
    sa_ignore.sa_handler = SIG_IGN;
    sa_ignore.sa_flags = 0;
    sigemptyset(&sa_ignore.sa_mask);
    sigaction(SIGINT, &sa_ignore, &sa_origint);
    sigaction(SIGQUIT, &sa_ignore, &sa_oquit);
    
    switch((id = fork())) {
        case -1:
            status = -1;
            break;
        case 0:
            sa_default.sa_handler = SIG_DFL;
            sa_default.sa_flags = 0;
            sigemptyset(&sa_default.sa_mask);
            if(sa_origint.sa_handler != SIG_IGN)
                sigaction(SIGINT, &sa_default, NULL);
            if(sa_oquit.sa_handler != SIG_IGN)
                sigaction(SIGQUIT, &sa_default, NULL);
            
            execl("/bin/sh", "sh", "-c", command.c_str(), (char*)NULL);
            _exit(127);
            break;
        default:
            while(waitpid(id, &status, 0) == -1) {
                if(errno != EINTR) {
                    status = -1;
                    break;
                }
            }
            break;
    }
    serrno = errno;
    sigprocmask(SIG_SETMASK, &omask, NULL);
    sigaction(SIGINT, &sa_origint, NULL);
    sigaction(SIGQUIT, &sa_oquit, NULL);
    errno = serrno;
    return status;
}


int main(int argc, char **argv) {
    if(argc != 4) {
        std::cerr << "Error: requires three arguments..\n";
        std::cerr << "use: \n" << argv[0] << " path \"command %f\" regex_search\n";
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
        System(r);
    }
    return 0;
}
