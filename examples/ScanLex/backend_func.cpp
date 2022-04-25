#include "backend_func.hpp"

namespace backend {

        Function::Function(void (*f)(std::vector<scan::Variable> &param, scan::Variable &result)) : func{f} {

        }

        void Function::call(std::vector<scan::Variable> &param, scan::Variable &re) {
            if(func != nullptr)
                func(param, re);
        }

        void FunctionTable::add(std::string name, const Function &f) {
            func_table[name] = f;
        }

}