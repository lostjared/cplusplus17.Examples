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

    void inputValue(std::vector<Variable> &param, Variable &result) {
        double val;
        std::cin >> val;
        result = Variable(val);
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
        func_table.add("scan", Function(inputValue));
    }

    void BackEnd::put(const Inc &i) {
        instruct.push_back(i);
        if(i.opc == O_LABEL) {
            labels[i.value1.value] = instruct.size()-1;
        } else if(i.opc == O_PROC) {
            procs[i.value1.value] = instruct.size()-1;
        }
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
                        d.type_info = VAR_DOUBLE;
                    }
                    break;
                    case O_SASSIGN: {
                        Variable var = popVar();
                        Variable &v = vars.getVar(instruct[ip].value1.name);
                        v.name = instruct[ip].value1.name;
                        v.value = var.value;
                        v.type_info = VAR_STRING;
                    }
                    break;
                    case O_PUSH: {
                            stack.push_back(instruct[ip].value1);
                    }
                    break;
                    case O_ADD:{
                        double value2 = popVal();
                        double value1 = popVal();
                        stack.push_back(scan::Variable(value1+value2));
                    }
                    break;
                    case O_SUB: {
                        double value2 = popVal();
                        double value1 = popVal();
                        stack.push_back(scan::Variable(value1-value2));
                    }
                    break;
                    case O_MUL: {
                        double value2 = popVal();
                        double value1 = popVal();
                        stack.push_back(scan::Variable(value1*value2));
                    }
                    break;
                    case O_DIV: {
                        double value2 = popVal();
                        double value1 = popVal();
                        if(value2 == 0) {
                            throw RuntimeException("Runtime Exception: Division by Zero");
                        }
                        stack.push_back(scan::Variable(value1/value2));
                    }
                    break;
                    case O_EE: {
                        Variable value2 = popVar();
                        Variable value1 = popVar();

                        if(value1.type_info == VAR_DOUBLE) {
                            runtimeTypeCheck(value2, VAR_DOUBLE);
                            stack.push_back(Variable(value1.val.fval == value2.val.fval));
                        } else {
                            stack.push_back(Variable(value1.value == value2.value));
                        }
                    }
                    break;
                    case O_NE: {
                        Variable value2 = popVar();
                        Variable value1 = popVar();
                        if(value1.type_info == VAR_DOUBLE) {
                            runtimeTypeCheck(value2, VAR_DOUBLE);
                            stack.push_back(Variable(value1.val.fval != value2.val.fval));
                        } else {
                            stack.push_back(Variable(value1.value != value2.value));
                        }
                    }
                    break;
                    case O_LT: {
                        Variable value2 = popVar();
                        Variable value1 = popVar();

                        runtimeTypeCheck(value1, VAR_DOUBLE);
                        runtimeTypeCheck(value2, VAR_DOUBLE);


                        if(value1.type_info == VAR_DOUBLE) {
                            stack.push_back(Variable(value1.val.fval < value2.val.fval));
                        } else {
                            stack.push_back(Variable(""));
                            //throw RuntimeException
                        }
                    }
                    break;
                    case O_GT: {
                        Variable value2 = popVar();
                        Variable value1 = popVar();

                        runtimeTypeCheck(value1, VAR_DOUBLE);
                        runtimeTypeCheck(value2, VAR_DOUBLE);

                        if(value1.type_info == VAR_DOUBLE) {
                            stack.push_back(Variable(value1.val.fval > value2.val.fval));
                        } else {
                            stack.push_back(Variable(""));
                        }
                    }
                    break;
                    case O_LTE: {
                        Variable value2 = popVar();
                        Variable value1 = popVar();

                        runtimeTypeCheck(value1, VAR_DOUBLE);
                        runtimeTypeCheck(value2, VAR_DOUBLE);

                        if(value1.type_info == VAR_DOUBLE) {
                            stack.push_back(Variable(value1.val.fval <= value2.val.fval));
                        } else {
                            stack.push_back(Variable(""));
                        }
                    }
                    break;
                    case O_GTE: {
                        Variable value2 = popVar();
                        Variable value1 = popVar();

                        runtimeTypeCheck(value1, VAR_DOUBLE);
                        runtimeTypeCheck(value2, VAR_DOUBLE);

                        if(value1.type_info == VAR_DOUBLE) {
                            stack.push_back(Variable(value1.val.fval >= value2.val.fval));
                        } else {
                            stack.push_back(Variable(""));
                        }
                    }
                    break;
                    // end todo
                    case O_CALL: {
                        std::string name = instruct[ip].value1.name;
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
                    case O_EXIT: {
                        throw RuntimeSuccess();
                    }
                    break;
                    case O_B: {
                        ip = labels[instruct[ip].value1.value];
                        continue;
                    }
                    break;
                    case O_BNE: {
                        Variable value = popVal();
                        if(value.val.fval == 0) {
                            ip = labels[instruct[ip].value1.value];
                            continue;
                        }
                    }
                    break;
                    default:
                    break;
                }
                ip++;
            }

        } catch(RuntimeException &e) {
            std::cerr << e.error() << "\n";
        } catch(RuntimeSuccess &s) {
            std::cout << "... exited normally.\n";
        }
        vars.print();
    }

    void BackEnd::print(std::ostream &out) {
        for(int i = 0; i < instruct.size(); ++i) {

            if(instruct[i].opc == O_LABEL) {
                out << instruct[i].value1.value << ":" << "\n";
                continue;
            }
            
            if(instruct[i].value1.type == VAR_EMPTY && instruct[i].value2.type == VAR_EMPTY)
                out << op_types[instruct[i].opc] << "\n";
            else if(instruct[i].value2.type == VAR_EMPTY)
                out << op_types[instruct[i].opc] << " " << instruct[i].value1 << "\n";
            else
            out << op_types[instruct[i].opc] << "  " << instruct[i].value1 << ", " << instruct[i].value2 << "\n";
        }
    }

    double BackEnd::popVal() {
        if(!stack.empty()) {
            Variable v = stack.back();
            stack.pop_back();
            runtimeTypeCheck(v, VAR_DOUBLE);
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
            if(v.name != "") {
                v.value = vars.getString(v.name);
                v.val.fval = vars.getDouble(v.name);
            }
            return v;
         } else {
            throw RuntimeException("Runtime Exception: Stack underflow");
        }
        return Variable();
    }

   void BackEnd::runtimeTypeCheck(const Variable &v, const VAR_TYPE_INFO &i) {
       if(v.type_info != i) {
           std::ostringstream stream;
           stream << "Type mismatch, expected: " << i << " found " << v.type_info;
           throw RuntimeException(stream.str());
       }
   }

}