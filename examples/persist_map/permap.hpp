#ifndef __PERMAP__H__
#define __PERMAP__H__

#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>

namespace persist {
    
    template<typename T>
    void GenericRead(std::fstream &file, T &type) {
        file.read(reinterpret_cast<char*>(&type), sizeof(type));
    }
    template<typename T>
    void GenericWrite(std::fstream &file, const T &type) {
        file.write(reinterpret_cast<const char*>(&type), sizeof(type));
    }
    
    template<typename T>
    class PersistMap {
    public:
        PersistMap() = delete;
        PersistMap(const PersistMap<T> &p);
        PersistMap(PersistMap<T> &&p);
        ~PersistMap();
        typedef void (*Read)(std::fstream &file, T &type);
        typedef void (*Write)(std::fstream &file, const T &type);
        PersistMap(std::string filename, Read re, Write wr);
        
        PersistMap<T> &operator=(const PersistMap<T> &p);
        PersistMap<T> &operator=(PersistMap<T> &&p);
        PersistMap<T> &operator<<(const PersistMap<T> &p);

        
        void WriteMap();
        void ReadMap();
        void EraseFile();
        T &operator[](const std::string &pos);
        void set(std::string key, const T &type);
        T &get(std::string key);
        void concat(const PersistMap<T> &p);
        std::unordered_map<std::string, T> *operator->();
        std::unordered_map<std::string, T> *Map();
    private:
        std::unordered_map<std::string, T> map_;
        Read read_;
        Write write_;
        std::string filename;
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
        for(auto i = p.map_.begin(); i != p.map_.end(); ++i) {
            auto [key,value] = *i;
            map_[key] = value;
        }
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
        std::cout << "Reading from disk...\n";
        std::fstream file;
        file.open(filename, std::ios::in | std::ios::binary);
        if(!file.is_open()) {
            return;
        }
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
        std::fstream file;
        file.open(filename, std::ios::out);
        file.close();
        map_.erase(map_.begin(), map_.end());
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
        this->operator<<(p);
    }
}

#endif
