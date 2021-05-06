#include<iostream>
#include<string>
#include<vector>

class Item {
public:
    std::string name;
    int value;
    Item() : value{0} {
        
    }
    Item(int vvalue, std::string nname) : value{vvalue}, name{nname} {}
    
    bool operator<(const Item &i) const {
        return value<i.value;
    }
};


int main(int argc, char **argv) {
    std::vector<Item> items;
    while(1) {
        std::cout << "Enter items: ";
        std::string i, n;
        std::cout << "enter sort rank: ";
        std::getline(std::cin, i);
        std::cout << "enter name: ";
        std::getline(std::cin, n);
        int v = atoi(i.c_str());
        Item index(v, n);
        items.push_back(index);
        std::sort(items.begin(), items.end());
        for(auto it = items.begin(); it != items.end(); ++it) {
            std::cout << it->value << ":" << it->name << "\n";
        }
    }
    return 0;
}
