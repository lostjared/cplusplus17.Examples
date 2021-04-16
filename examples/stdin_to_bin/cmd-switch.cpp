#include"cmd-switch.hpp"

namespace cmd {

    ArgumentStringList::ArgumentStringList(int argc, char **argv) : argz {argc,argv} {
    
    }
    
    bool Argument_FindInList(std::vector<std::string> &lst, ArgumentStringList &alst) {
        for(int i = 0; i < alst.argz.size(); ++i) {
            bool found = false;
            for(int z = 0; z < lst.size(); ++z) {
                if(alst.argz.item(i).key == "$") {
                    if(alst.argz.item(i).value == lst[z]) {
                        found = true;
                        break;
                    }
                } else {
                    if(alst.argz.item(i).key == lst[z]) {
                        found = true;
                        break;
                    }
                }
            }
            if(found == true)
                return true;
        }
        return false;
    }

    std::string _tolower(const std::string &str) {
        std::string temp;
        for(int i = 0; i < str.length(); ++i) {
            temp += tolower(str[i]);
        }
        return temp;
    }
    
    std::string _toupper(const std::string &str) {
        std::string temp;
        for(int i = 0; i < str.length(); ++i) {
            temp += toupper(str[i]);
        }
        return temp;
    }
}
