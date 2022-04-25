#ifndef __BACKEND_H_FUNC_
#define __BACKEND_H_FUNC_


#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include"scan_symbol.hpp"

namespace backend {


    class Function {
    public:
        Function() = default;
        Function(void (*f)(std::vector<scan::Variable> &param, scan::Variable &result));
        void (*func)(std::vector<scan::Variable> &parameters, scan::Variable &result) = nullptr;
        void call(std::vector<scan::Variable> &param, scan::Variable &result);
    };

    class FunctionTable {
    public:
        std::unordered_map<std::string, Function> func_table;
        void add(std::string name, const Function &f);
    };

}

#endif