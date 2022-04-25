#include "backend_func.hpp"

namespace backend {

        Function::Function(void (*f)(std::vector<scan::Variable> &param, scan::Variable &result)) : func{f} {

        }

        void Function::call(std::vector<scan::Variable> &param, scan::Variable &re) {
            if(func != nullptr)
                func(param, re);
        }

        void FunctionTable::add(const std::string &name, const Function &f) {
            func_table[name] = f;
        }

        bool FunctionTable::valid(const std::string &n) {
            if(func_table.find(n) != func_table.end())
                return true;
            return false;
        }

}