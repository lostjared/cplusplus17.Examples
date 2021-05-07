#include<iostream>
#include<string>
#include<list>

// from Compilers PT&T
unsigned int hash(const std::string &key, unsigned int size) {
    unsigned int val = 0;
    const char *ptr = key.c_str();
    while(*ptr != '\0') {
        unsigned int tmp;
        val = (val << 4) + (*ptr);
        if((tmp = (val & 0xf00000000))) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }
        ptr++;
    }
    return val%size;
}

template<int Size, typename T>
class Table {
  
public:
    Table() = default;
    void enter(std::string key, const T &type) {
        unsigned int k = hash(key, Size);
        for(auto it = buckets[k].begin(); it != buckets[k].end(); ++it) {
            if(it->first == key) {
                it->second = type;
                return;
            }
        }
        buckets[k].push_back(std::make_pair(key, type));
    }
    
    bool lookup(std::string key, T &type) {
        int k = hash(key, Size);
        for(auto it = buckets[k].begin(); it != buckets[k].end(); ++it) {
            if(it->first == key) {
                type = it->second;
                return true;
            }
        }
        return false;
    }
    
    void erase(std::string key) {
        int k = hash(key, Size);
        for(auto it = buckets[k].begin(); it != buckets[k].end(); ++it) {
            if(it->first == key) {
                buckets[k].erase(it);
                return;
            }
        }
    }

protected:
    std::list<std::pair<std::string, T>> buckets[Size];
    
};

int main(int argc, char **argv) {
    
    Table<100, std::string> table;
    
    table.enter("apple", "tree");
    table.enter("bear", "animal");
    
    std::string apple;
    if(table.lookup("apple", apple)) {
        std::cout << apple << "\n";
    }
    table.erase("apple");
    if(table.lookup("apple", apple)) {
        std::cout << apple << "\n";
    }
    
    return 0;
}
