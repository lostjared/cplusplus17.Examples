// Enter quit for the requested key to quit program
// Enter erase to erase file/map

#include"permap.hpp"
#include<algorithm>
#include<cstdlib>

int main() {
    persist::PersistMap<int> int_map("int.txt",persist::GenericRead<int>, persist::GenericWrite<int>);
    while(1) {
        std::string key,value;
        std::cout << "Enter key: ";
        std::getline(std::cin, key);
        if(key == "quit") break;
        if(key == "erase") {
            int_map.EraseFile();
            std::cout << "Erased..\n";
            continue;
        }
        std::cout << "Enter value: ";
        std::getline(std::cin, value);
        int_map[key] = atoi(value.c_str());
        
        std::cout << "\n\nCurrent Values: \n";
        for(auto i = int_map->begin(); i != int_map->end(); ++i) {
            auto [map_key, map_value] = *i;
            std::cout << map_key << " = " << map_value << "\n";
        }
    }
    return 0;
}
