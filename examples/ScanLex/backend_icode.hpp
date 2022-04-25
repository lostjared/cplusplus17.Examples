#ifndef _BACKEND_ICODE_H_
#define _BACKEND_ICODE_H_

#include<iostream>
#include<string>
#include"backend_func.hpp"

namespace backend {

    enum OPERATION_TYPE { O_ADD, O_SUB, O_MUL, O_DIV, O_CALL, O_PUSH };
    static const char *op_types[] = {"ADD", "SUB", "MUL", "DIV", "CALL", "PUSH", 0};

    class Inc {
    public:
        OPERATION_TYPE opc;
        scan::Variable value1;
        scan::Variable value2;
        Inc() = default;
        Inc(OPERATION_TYPE o, const scan::Variable &v, const scan::Variable &v2);
    };

    class BackEnd {
    public:
        BackEnd();
        void put(const Inc &i);
        void go();
        void print(std::ostream &out);
    protected:
        std::vector<Inc> instruct;
        std::vector<scan::Variable> stack;
        FunctionTable func_table;
    };

}

#endif