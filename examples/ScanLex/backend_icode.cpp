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

    }

    void BackEnd::print(std::ostream &out) {
        for(int i = 0; i < instruct.size(); ++i) {
            out << op_types[instruct[i].opc] << "  " << instruct[i].value1 << ", " << instruct[i].value2 << "\n";
        }
    }

}