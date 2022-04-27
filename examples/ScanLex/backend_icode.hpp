#ifndef _BACKEND_ICODE_H_
#define _BACKEND_ICODE_H_

#include<iostream>
#include<string>
#include"backend_func.hpp"

namespace backend {

    using namespace scan;

    enum OPERATION_TYPE { O_SASSIGN, O_ASSIGN, O_ADD, O_SUB, O_MUL, O_DIV, O_CALL, O_PUSH, O_POP, O_EE, O_NE };
    static const char *op_types[] = {"SASSIGN", "ASSIGN", "ADD", "SUB", "MUL", "DIV", "CALL", "PUSH","POP","EE","NE", 0};

    class RuntimeException {
    public:
        RuntimeException() = default;
        RuntimeException(const std::string &s);
        std::string error();
    protected:
        std::string text;
    };


    class Inc {
    public:
        OPERATION_TYPE opc;
        Variable value1;
        Variable value2;
        Inc() = default;
        Inc(OPERATION_TYPE o, const Variable &v, const Variable &v2);
    };

    class BackEnd {
    public:
        BackEnd();
        void put(const Inc &i);
        void go();
        void print(std::ostream &out);
        void decl(const std::string &var, double d);
        void decl(const std::string &var, const std::string &value);
    protected:
        std::vector<Inc> instruct;
        std::vector<Variable> stack;
        FunctionTable func_table;
        SymbolTable vars;
        double popVal();
        Variable popVar();
    };

}

#endif