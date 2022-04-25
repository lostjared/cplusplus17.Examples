#include"backend_icode.hpp"

namespace backend {


    RuntimeException::RuntimeException(const std::string &s) : text{s} {

    }
    
    std::string RuntimeException::error() {
        return text;
    }


    void addOne(std::vector<scan::Variable> &param, scan::Variable &result) {
        if(param.size()==1)
            result.val.fval = param[0].val.fval + 1;
    }

    void printEcho(std::vector<Variable> &param, Variable &result) {
        if(param.size()==1) {
            if(param[0].type == VAR_CONST) {
                switch(param[0].type_info) {
                    case VAR_DOUBLE:
                        std::cout << param[0].val.fval << "\n";
                        break;
                    case VAR_STRING:
                        std::cout << param[0].value << "\n";
                        break;
                        default:
                        break;
                }
            } 
        }
    }

    Inc::Inc(OPERATION_TYPE o, const scan::Variable &v, const scan::Variable &v2) : opc{o}, value1{v}, value2{v2} {

    }

    BackEnd::BackEnd() {
        func_table.add("test", Function(addOne));
        func_table.add("echo", Function(printEcho));
    }

    void BackEnd::put(const Inc &i) {
        instruct.push_back(i);
    }

    void BackEnd::decl(const std::string &var, double d) {
        vars.enter(var, d);
    }
    
    void BackEnd::decl(const std::string &var, const std::string &value) {
        vars.enter(var, value);
    }

    
    void BackEnd::go() {
        try {
            int ip = 0;
            while(ip < instruct.size()) {
                OPERATION_TYPE type = instruct[ip].opc;
                switch(type) {
                    case O_ASSIGN: {
                        double v = popVal();
                        double &d = vars.getDouble(instruct[ip].value1.name);
                        d = v; 
                        std::cout << instruct[ip].value1.name << " = " << d << "\n";                       
                    }
                    break;
                    case O_PUSH: {
                        stack.push_back(instruct[ip].value1);
                    }
                    break;
                    case O_ADD:{
                        double value1 = popVal();
                        double value2 = popVal();
                        stack.push_back(scan::Variable(value1+value2));
                    }
                    break;
                    case O_SUB: {
                        double value1 = popVal();
                        double value2 = popVal();
                        stack.push_back(scan::Variable(value1-value2));
                    }
                    break;
                    case O_MUL: {
                        double value1 = popVal();
                        double value2 = popVal();
                        stack.push_back(scan::Variable(value1*value2));
                    }
                    break;
                    case O_DIV: {
                        double value1 = popVal();
                        double value2 = popVal();
                        stack.push_back(scan::Variable(value1/value2));
                    }
                    break;
                    case O_CALL: {
                        std::string name = instruct[ip].value1.value;
                        double val = popVal();
                        std::vector<scan::Variable> v;
                        v.push_back(Variable(val));
                        scan::Variable result;
                        func_table.func_table[name].call(v, result);
                        stack.push_back(result);                      
                    }
                    break;
                    default:
                    break;
                }
                ip++;
            }

        } catch(RuntimeException &e) {
            std::cerr << e.error() << "\n";
        }
    }

    void BackEnd::print(std::ostream &out) {
        for(int i = 0; i < instruct.size(); ++i) {
            out << op_types[instruct[i].opc] << "  " << instruct[i].value1 << ", " << instruct[i].value2 << "\n";
        }
        vars.print();
    }

    double BackEnd::popVal() {
        if(!stack.empty()) {
            Variable v = stack.back();
            stack.pop_back();
        
            if(v.type == VAR_CONST)
                return v.val.fval;
        
            if(v.type == VAR_VAR) {
                return vars.getDouble(v.name); 
            }
        }
        return 0;
    }


}