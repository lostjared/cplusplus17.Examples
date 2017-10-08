// Enter quit for the requested key to quit program

#include "permap.hpp"
#include<algorithm>

int main() {
    
    persist::PersistMap<std::string> string_data("data.txt", [](std::fstream &file, std::string &val) {
        unsigned int value;
        file.read(reinterpret_cast<char*>(&value), sizeof(value));
        char *buf = new char[value+1];
        file.read(buf, value);
        buf[value] = 0;
        val = buf;
        delete [] buf;
    },
    [](std::fstream &file, const std::string &val) {
        unsigned int value = val.length();
        file.write(reinterpret_cast<char*>(&value), sizeof(value));
        file.write(val.c_str(), value);
    });
    while(1) {
    	std::cout << "Enter key: ";
    	std::string key_text;
    	std::getline(std::cin, key_text);
        if(key_text == "quit") break;
    	std::cout << "Enter key value: ";
    	std::string key_value;
    	std::getline(std::cin, key_value);
        string_data[key_text] = key_value;
        for (auto i = string_data->begin(); i != string_data->end(); ++i) {
            auto [s_key, s_value] = *i;
            std::cout << s_key << " = " << s_value << "\n";
        }
    }
    return 0;
}
