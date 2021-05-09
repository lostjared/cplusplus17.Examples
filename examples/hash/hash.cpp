// Just practicing some different ideas and concepts
// chained hash table

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

template<typename T, unsigned int Size>
class Table {
  
public:
    Table() = default;

    T &operator[](const std::string &key) {
        int k = hash(key, Size);
        for(auto it = buckets[k].begin(); it != buckets[k].end(); it++) {
            if(it->first == key)
                return it->second;
        }
        buckets[k].push_back(std::make_pair(key, T()));
        auto it = buckets[k].begin();
        for(; it != buckets[k].end(); it++) {
            if(it->first == key)
                break;
        }
        return it->second;
    }
    
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
    
    Table<std::string, 1024> table;
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
    
    table["order"] = "pie";
    std::cout << table["order"] << "\n";
    
    return 0;
}
