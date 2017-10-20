#ifndef __PERMAP__H__
#define __PERMAP__H__

#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>

namespace persist {
    
    // for generic read for built in types/structs
    template<typename T>
    void GenericRead(std::fstream &file, T &type) {
        file.read(reinterpret_cast<char*>(&type), sizeof(type));
    }
    // for generic write for built in types/structs
    template<typename T>
    void GenericWrite(std::fstream &file, const T &type) {
        file.write(reinterpret_cast<const char*>(&type), sizeof(type));
    }
    // read of string class
    void StringRead(std::fstream &file, std::string &type) {
        unsigned int len = 0;
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        if(len > 0) {
        	char *buf = new char [len+1];
            file.read(buf, len);
            buf[len] = 0;
            type = buf;
            delete [] buf;
        } else {
            std::cerr << "Error on string read..\n";
        }
    }
    // write of string class
    void StringWrite(std::fstream &file, const std::string &type) {
        unsigned int len = type.length();
        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        file.write(type.c_str(), len);
    }
    
    // Persistent Hash Table
    template<typename T>
    class PersistMap {
    public:
        // the Read/Write functions for T
        using Read = void (*)(std::fstream &file, T &type);
        using Write = void (*)(std::fstream &file, const T &type);
        // default constructor not available
        PersistMap() = delete;
        PersistMap(const PersistMap<T> &p);
        PersistMap(PersistMap<T> &&p);
        ~PersistMap();
        // Constructor pass filename for file, Read/Write functions for T
        PersistMap(std::string filename, Read re, Write wr);
        // overloaded operators
        PersistMap<T> &operator=(const PersistMap<T> &p);
        PersistMap<T> &operator=(PersistMap<T> &&p);
        PersistMap<T> &operator<<(const PersistMap<T> &p);
        // File stuff Read/Write Map / Erase File
        void WriteMap();
        void ReadMap();
        void EraseFile();
        // does a given key exisit?
        bool key_exisits(const std::string &text);
        // [] overlaoded operator for accessing data by key
        T &operator[](const std::string &pos);
        // set/get functions
        void set(std::string key, const T &type);
        T &get(std::string key);
        // concat merge map of same type
        void concat(const PersistMap<T> &p);
        // overloaded -> operator for accessing unordered_map
        std::unordered_map<std::string, T> *operator->();
        std::unordered_map<std::string, T> *Map();
    private:
        std::unordered_map<std::string, T> map_; // the map
        Read read_;
        Write write_;
        std::string filename; // filename
    };
    
    template<typename T>
    PersistMap<T>::PersistMap(const PersistMap<T> &p) : map_(p.map_), read_(p.read_), write_(p.write_), filename(p.filename) {
        ReadMap();
    }
    
    template<typename T>
    PersistMap<T>::PersistMap(PersistMap<T> &&p) : map_(std::move(p.map_)), read_(p.read_), write_(p.write), filename(p.filename) {
        ReadMap();
    }
    
    template<typename T>
    PersistMap<T>::PersistMap(std::string filen, Read re, Write wr) : read_(re), write_(wr), filename(filen) {
        ReadMap();
    }
    
    template<typename T>
    PersistMap<T>::~PersistMap() {
        WriteMap();
    }
    
    
    template<typename T>
    PersistMap<T> &PersistMap<T>::operator=(const PersistMap<T> &p) {
        map_ = p.map_;
        read_ = p.read_;
        write_ = p.write_;
        filename = p.filename;
        return *this;
    }
    
    template<typename T>
    PersistMap<T> &PersistMap<T>::operator=(PersistMap<T> &&p) {
        map_ = std::move(p.map_);
        read_ = p.read_;
        write_ = p.write_;
        filename = p.filename;
        return *this;
    }
    
    template<typename T>
    PersistMap<T> &PersistMap<T>::operator<<(const PersistMap<T> &p) {
        concat(p);
        return *this;
    }
    
    template<typename T>
    T &PersistMap<T>::operator[](const std::string &pos) {
        return map_[pos];
    }
    
    template<typename T>
    void PersistMap<T>::WriteMap() {
        std::cout << "Writing to disk...\n";
        std::fstream file;
        file.open(filename, std::ios::out | std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Error file: " << filename << " could not be opened.\n";
            return;
        }
        for(auto i = map_.begin(); i != map_.end(); ++i) {
            std::string val = i->first;
            unsigned int value = val.length();
            file.write(reinterpret_cast<char*>(&value), sizeof(value));
            file.write(val.c_str(), value);
            write_(file, i->second);
        }
        file.close();
    }
    template<typename T>
    void PersistMap<T>::ReadMap() {
         std::fstream file;
        file.open(filename, std::ios::in | std::ios::binary);
        if(!file.is_open()) {
            std::cout << "New file...\n";
            return;
        }
        std::cout << "Reading from disk...\n";
        while(!file.eof()) {
            std::string key;
            unsigned int value = 0;
            file.read(reinterpret_cast<char*>(&value), sizeof(value));
            char *buf = new char[value+1];
            file.read(buf, value);
            buf[value] = 0;
            key = buf;
            delete [] buf;
            T type;
            read_(file,type);
            if(key.length()>0)
                map_[key] = type;
        }
        file.close();
    }
    
    template<typename T>
    void PersistMap<T>::EraseFile() {
        map_.erase(map_.begin(), map_.end());
        WriteMap();
    }
    template<typename T>
    bool PersistMap<T>::key_exisits(const std::string &text) {
        auto index = map_.find(text);
        if(index == map_.end()) return false;
        return true;
    }
    
    template<typename T>
    std::unordered_map<std::string, T> *PersistMap<T>::operator->() {
        return &map_;
    }
    
    template<typename T>
    std::unordered_map<std::string, T> *PersistMap<T>::Map() {
        return &map_;
    }
    
    template<typename T>
    void PersistMap<T>::set(std::string key, const T &type) {
        map_[key] = type;
    }
    template<typename T>
    T &PersistMap<T>::get(std::string key) {
        return map_[key];
    }
    template<typename T>
    void PersistMap<T>::concat(const PersistMap<T> &p) {
        for(auto i = p.map_.begin(); i != p.map_.end(); ++i) {
            auto [key,value] = *i;
            map_[key] = value;
        }
    }
}

#endif
