#include"backend_icode.hpp"

namespace backend {


    void addOne(std::vector<scan::Variable> &param, scan::Variable &result) {
        result.val.fval = param[0].val.fval + 1;
    }

    Inc::Inc(OPERATION_TYPE o, const scan::Variable &v, const scan::Variable &v2) : opc{o}, value1{v}, value2{v2} {

    }

    BackEnd::BackEnd() {
        func_table.add("test", Function(addOne));
    }

    void BackEnd::put(const Inc &i) {
        instruct.push_back(i);
    }
    
    void BackEnd::go() {
        int ip = 0;
        while(ip < instruct.size()) {
            OPERATION_TYPE type = instruct[ip].opc;
            switch(type) {
                case O_PUSH: {
                    stack.push_back(instruct[ip].value1);
                }
                break;
                case O_ADD:{
                    scan::Variable value1 = stack.back();
                    stack.pop_back();
                    scan::Variable value2 = stack.back();
                    stack.pop_back();
                    stack.push_back(scan::Variable(value1.val.fval+value2.val.fval));
                }
                break;
                case O_SUB: {
                    scan::Variable value1 = stack.back();
                    stack.pop_back();
                    scan::Variable value2 = stack.back();
                    stack.pop_back();
                    stack.push_back(scan::Variable(value1.val.fval-value2.val.fval));
                }
                break;
                case O_MUL: {
                    scan::Variable value1 = stack.back();
                    stack.pop_back();
                    scan::Variable value2 = stack.back();
                    stack.pop_back();
                    stack.push_back(scan::Variable(value1.val.fval*value2.val.fval));
                }
                break;
                case O_DIV: {
                    scan::Variable value1 = stack.back();
                    stack.pop_back();
                    scan::Variable value2 = stack.back();
                    stack.pop_back();
                    // check for division by zero
                    stack.push_back(scan::Variable(value1.val.fval/value2.val.fval));
                }
                break;
                case O_CALL: {
                    std::string name = instruct[ip].value1.value;
                    scan::Variable val = stack.back();
                    std::vector<scan::Variable> v;
                    v.push_back(val);
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
        std::cout << "Result: " << stack.back() << "\n";
        stack.pop_back();
    }

    void BackEnd::print(std::ostream &out) {
        for(int i = 0; i < instruct.size(); ++i) {
            out << op_types[instruct[i].opc] << "  " << instruct[i].value1 << ", " << instruct[i].value2 << "\n";
        }
    }

}