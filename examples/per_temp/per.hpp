// practice to get the hang of it again
// it's starting to come back

#ifndef __PER__H__
#define __PER__H__

#include<iostream>
#include<string>
#include<fstream>

namespace per {

    template<typename T>
    class Data {
    public:
        Data() = default;
        static void write(std::fstream &file, const T &type) {
            if(file.is_open())
                file.write(reinterpret_cast<const char*>(&type), sizeof(type));
        }
        static void read(std::fstream &file, T &type) {
            if(file.is_open())
                file.read(reinterpret_cast<char*>(&type), sizeof(type));
        }
    };

    class StringData {
    public:
        StringData() = default;
        static void write(std::fstream &file, const std::string &type) {
            if(file.is_open()) {
                int len = type.length();
                file.write(reinterpret_cast<const char *>(&len), sizeof(len));
                file.write(reinterpret_cast<const char *>(type.c_str()), len);
            }
        }
        static void read(std::fstream &file, std::string &type) {
            if(file.is_open()) {
                int len;
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                char *buf = new char [len + 1];
                file.read(buf, len);
                buf[len] = 0;
                type = buf;
                delete [] buf;
            }
        }
    };

    template<typename C>
    class StringContainerData {
    public:
        StringContainerData() = default;
        static void write(std::fstream &file, const C &type) {
            if(file.is_open()) {
                for(auto it = type.begin(); it != type.end(); ++it) {
                    int len = it->length();
                    file.write(reinterpret_cast<const char *>(&len), sizeof(len));
                    file.write(reinterpret_cast<const char *>(it->c_str()), len);
                }
            }
        }
        static void read(std::fstream &file, C &type) {
            if(file.is_open()) {
                while(!file.eof()) {
                    int len;
                    file.read(reinterpret_cast<char*>(&len), sizeof(len));
                    if(file) {
                        char *buf = new char [len + 1];
                        file.read(buf, len);
                        buf[len] = 0;
                        std::string t{buf};
                        delete [] buf;
                        type.push_back(t);
                    }
                }
            }
        }
    };

    template<typename C, typename T>
    class ContainerData {
    public:
        ContainerData() = default;
        static void write(std::fstream &file, const C &type) {
            if(file.is_open()) {
                for(auto i = type.begin(); i != type.end(); ++i) {
                    file.write(reinterpret_cast<const char *>(&*i), sizeof(*i));
                }
            }
        }
        static void read(std::fstream &file, C &type) {
            if(file.is_open()) {
                while(!file.eof()) {
                    T t;
                    file.read(reinterpret_cast<char*>(&t), sizeof(t));
                    if(file)
                        type.push_back(t);
                    else
                        break;
                }
            }
        }
    };

    template<typename T, typename D = Data<T>>
    class Per {
    public:
                
        Per(std::string name) : file_name{name} {
            load();
        }
        
        Per(std::string name, const T &i) : file_name{name} {
            std::fstream file_in;
            file_in.open(file_name, std::ios::in | std::ios::binary);
            if(!file_in.is_open()) {
                type = i;
            } else {
                file_in.close();
                load();
            }
        }
        
        // must reassign filename
        Per(const Per<T,D> &p, const std::string &file_n) : file_name{file_n}, type{p.type} {}
        Per(const Per<T,D> &&p, const std::string &file_n) : file_name{file_n}, type{std::move(p.type)} {}
        
        // prevent
        Per<T,D> &operator=(const Per<T,D> &p) = delete;
        Per<T,D> &operator=(const Per<T,D> &&p) = delete;
        
        // assignment
        Per<T,D> &operator=(const T &t) {
            type = t;
            return *this;
        }
        Per<T,D> &operator=(const T &&t) {
            type = std::move(t);
            return *this;
        }
        
        void save() {
            std::fstream file_in;
            file_in.open(file_name, std::ios::out | std::ios::binary | std::ios::trunc);
            if(!file_in.is_open()) {
                std::cerr << "Error could not open: " << file_name << " for output...\n";
                exit(EXIT_FAILURE);
            }
            D::write(file_in, type);
            file_in.close();
        }
        
        void load() {
            std::fstream file_in;
            file_in.open(file_name, std::ios::in |  std::ios::binary);
            if(file_in.is_open()) {
                D::read(file_in, type);
                file_in.close();
            }
        }
        
        void set(const T &t) {
            type = t;
        }
        
        void reset() {
            type = T();
        }
        
        void clear() {
            reset();
            save();
        }
        
        ~Per() {
            save();
        }
        
        T &data() { return type; }
        T &operator*() { return type; }

    private:
        T type;
        std::string file_name;
    };
}

#endif


