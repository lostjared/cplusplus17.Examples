#include"backend_icode.hpp"
#include<sstream>
#include<algorithm>

namespace backend {


    RuntimeException::RuntimeException(const std::string &s) : text{s} {

    }
    
    std::string RuntimeException::error() {
        return text;
    }


    void addOne(std::vector<scan::Variable> &param, scan::Variable &result) {
        if(param.size()==1) {
            result = Variable(param[0].val.fval+1);
        }
    }

    void decOne(std::vector<Variable> &param, Variable &result) {
        if(param.size() == 1) {
            result = Variable(param[0].val.fval-1);
        }
    }

    void printEcho(std::vector<Variable> &param, Variable &result) {
        for(int i =0; i < param.size(); ++i) {
           if(param[i].type == VAR_CONST) {
                    switch(param[i].type_info) {
                        case VAR_DOUBLE:
                        std::cout << param[i].val.fval;
                        break;
                    case VAR_STRING:
                            std::cout << param[i].value;
                        break;
                    default:
                         break;
                }
            }  else {
                std::cout << param[i].value;
            }
        }
        result = Variable(double(param.size()));
        std::cout << "\n";
    }

    void printList(std::vector<Variable> &param, Variable &result) {
        std::cout << "( ";
        for(int i = 0; i < param.size(); ++i) {
            if(param[i].type == VAR_CONST) {
                switch(param[i].type_info) {
                    case VAR_DOUBLE:
                        std::cout << param[i].val.fval << " ";
                        break;
                    case VAR_STRING:
                        std::cout << param[i].value << " ";
                        break;
                        default:
                        break;
                }
            } else {
                std::cout << "VAR VAR\n";
            }      
        }
        std::cout << ")\n";
        result = Variable(param.size());
    }

    void stringLength(std::vector<Variable> &param, Variable &result) {
        if(param.size()==1) {
            result = Variable(param[0].value.length());
            return;
        }
        result = Variable(0);
    }

    Inc::Inc(OPERATION_TYPE o, const scan::Variable &v, const scan::Variable &v2) : opc{o}, value1{v}, value2{v2} {

    }

    BackEnd::BackEnd() {
        func_table.add("inc", Function(addOne));
        func_table.add("dec", Function(decOne));
        func_table.add("echo", Function(printEcho));
        func_table.add("list", Function(printList));
        func_table.add("strlen", Function(stringLength));
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
                    case O_POP:
                    if(!stack.empty()) {
                        stack.pop_back();
                    }
                    break;
                    case O_ASSIGN: {
                        double v = popVal();
                        Variable &d = vars.getVar(instruct[ip].value1.name);
                        d.val.fval = v;
                    }
                    break;
                    case O_SASSIGN: {
                        Variable var = popVar();
                        Variable &v = vars.getVar(instruct[ip].value1.name);
                        v.name = instruct[ip].value1.name;
                        v.value = var.value;
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
                        if(value2 == 0) {
                            throw RuntimeException("Runtime Exception: Division by Zero");
                        }
                        stack.push_back(scan::Variable(value1/value2));
                    }
                    break;
                    case O_CALL: {
                        std::string name = instruct[ip].value1.value;
                        std::vector<scan::Variable> v;
                        int n = static_cast<int>(instruct[ip].value2.val.fval);
                        for(int i = 0; i < n; ++i) {
                           Variable val = popVar();
                           if(val.name != "") {
                              v.push_back(vars.getVar(val.name));
                           } else 
                            v.push_back(val);
                        }
                        scan::Variable result;
                        if(!func_table.valid(name)) {
                            std::ostringstream stream;
                            stream << "Runtime Exception: " << name << " function not found!";
                            throw RuntimeException(stream.str());
                        }
                        std::reverse(v.begin(), v.end());
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
        
        if(!stack.empty()) {
            for(int i = 0; i < stack.size(); ++i)
                std::cout << i << ": " << stack[i] << "\n";
        }
        std::cout << "Stack Size: " << stack.size() << "\n";

        vars.print();
    }

    void BackEnd::print(std::ostream &out) {
        for(int i = 0; i < instruct.size(); ++i) {
            out << op_types[instruct[i].opc] << "  " << instruct[i].value1 << ", " << instruct[i].value2 << "\n";
        }
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
        } else {
            throw RuntimeException("Runtime Exception: Stack underflow");
        }
        return 0;
    }

    Variable BackEnd::popVar() {
        if(!stack.empty()) {
            Variable v = stack.back(); 
            
            stack.pop_back();
            return v;
         } else {
            throw RuntimeException("Runtime Exception: Stack underflow");
        }
        return Variable();
    }
}