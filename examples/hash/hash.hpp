#ifndef _HASH_HPP__H__
#define _HASH_HPP__H__

#include<iostream>
#include<string>
#include<list>

namespace htable {
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
            for(auto & [first,second] : buckets[k]) {
                if(first == key)
                    return second;
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
            for(auto & [first, second] : buckets[k]) {
                if(first == key) {
                    second = type;
                    return;
                }
            }
            buckets[k].push_back(std::make_pair(key, type));
        }
        
        bool lookup(std::string key, T &type) {
            int k = hash(key, Size);
            for(auto & [first, second] : buckets[k]) {
                if(first == key) {
                    type = second;
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
        
        const int size() const { return Size; }
        std::list<std::pair<std::string, T>> &at(unsigned int pos) { return buckets[pos]; }
        
    protected:
        std::list<std::pair<std::string, T>> buckets[Size];
        
    };

}

#endif

