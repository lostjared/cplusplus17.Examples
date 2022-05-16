#ifndef _BACKEND_ICODE_H_
#define _BACKEND_ICODE_H_

#include<iostream>
#include<string>
#include<unordered_map>
#include"backend_func.hpp"

namespace backend {

    using namespace scan;

    enum OPERATION_TYPE { O_LABEL=0, O_SASSIGN, O_ASSIGN, O_ADD, O_SUB, O_MUL, O_DIV, O_CALL, O_PUSH, O_POP, O_EE, O_NE, O_LT, O_GT, O_LTE, O_GTE, O_B, O_BNE, O_BE, O_JE, O_EXIT, O_PROC, O_RET };
    static const char *op_types[] = {"LABEL", "SASSIGN", "ASSIGN", "ADD", "SUB", "MUL", "DIV", "CALL", "PUSH","POP","EE","NE","LT","GT", "LTE", "GTE","B", "BNE", "BE", "JE", "EXIT", "PROC","RET", 0};

    class RuntimeException {
    public:
        RuntimeException() = default;
        RuntimeException(const std::string &s);
        std::string error();
    protected:
        std::string text;
    };

    class RuntimeSuccess {};


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
        void runtimeTypeCheck(const Variable &v, const VAR_TYPE_INFO &i);
        int lookupLabel(const std::string &name);
    protected:
        std::vector<Inc> instruct;
        std::vector<Variable> stack;
        FunctionTable func_table;
        SymbolTable vars;
        double popVal();
        Variable popVar();
        std::unordered_map<std::string, int> labels;
        std::unordered_map<std::string, int> procs;
    };

}

#endif