#ifndef __RDWR__H__
#define __RDWR__H__

#include<iostream>
#include<string>

namespace System {
    
    class output {
    public:
        output() = default;
        
        template<typename T>
        void println(const T &type) {
            std::cout << type;
        }
        
        template<typename T, typename... Args>
        void println(const T &type, Args... args) {
            println(type);
            println(args...);
            if(sizeof...(args) == 1) std::cout << "\n";
        }
        
        template<typename T>
        void print(const T &type) {
            std::cout << type;
        }
        
        template<typename T, typename... Args>
        void print(const T &type, Args... args) {
            print(type);
            print(args...);
        }
    };
    
    class input {
    public:
        input() = default;
        template<typename T>
        void read(T &type) {
            std::cin >> type;
        }
    };

    inline output out;
    inline input  in;
}

#endif
