#include"cmd-switch.hpp"

namespace cmd {

    ArgumentList::ArgumentList(int argc, char **argv) {
        for(int i = 1; i < argc; ++i) {
            std::string s = argv[i];
            auto pos = s.find("=");
            if(pos != std::string::npos) {
                std::string left = s.substr(0, pos);
                std::string right = s.substr(pos+1, s.length());
                if(right.length() == 0)
                    throw ArgExcep<std::string>("Argument Error: Zero Length");
                
                Token<std::string> token;
                token.key = left;
                token.value = right;
                items.push_back(token);
            } else {
                Token<std::string> token;
                token.key = "$";
                token.value = argv[i];
                items.push_back(token);
            }
        }
    }
    
    bool ArgumentList::check(std::string key) {
        for(int i = 0; i < items.size(); ++i) {
            if(items[i].key == "$") {
                if(items[i].value == key) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool ArgumentList::extract(std::string key, std::string &value) {
        for(int i = 0; i < items.size(); ++i) {
            if(items[i].key == "$" && items[i].value == key) {
                return false;
            }
            if(items[i].key == key) {
                value = items[i].value;
                return true;
            }
        }
        return false;
    }

    bool ArgumentList::require(std::string key, std::string &value) {
        for(int i = 0; i < items.size(); ++i) {
            
            if(items[i].key == "$" && items[i].value == key) {
                throw ArgExcep<std::string>("Argument Error: " + key + " required argument missing value...");
                return false;
            }
            
            if(items[i].key == key) {
                value = items[i].value;
                return true;
            }
        }
        throw ArgExcep<std::string>("Argument Error: " + key + " Required");
        return false;
    }
}
