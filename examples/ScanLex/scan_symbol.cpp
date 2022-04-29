#include"scan_symbol.hpp"

namespace scan {

   std::ostream &operator<<(std::ostream &out, const Variable &v) {

       if(v.name != "") {
           out << v.name;
           return out;
       }

       switch(v.type) {
           case VAR_CONST:
           switch(v.type_info) {
               case VAR_DOUBLE:
               out << v.val.fval;
               return out;
               break;
               case VAR_STRING:
               out << "\"" << v.value << "\"";
               return out;
               break;
               default:
               break;
           }
           break;
           case VAR_VAR:
           out << v.name;
           return out;
           break;
           default:
           break;
       }
       out << "(unused)";
       return out;
   }

   std::ostream &operator<<(std::ostream &out, const VAR_TYPE_INFO &v) {
       switch(v) {
           case VAR_DOUBLE:
           case VAR_STRING:
           case VAR_ID:
           case VAR_ARRAY:
           out << vtype_info[v];
           break;
           default:
           out << v;
           break;
       }
       return out;
   }

   void Variable::copy(const Variable &v) {
        name = v.name;
        value = v.value;
        val = v.val;
        index = v.index;
        id = v.id;
        type = v.type;
        type_info = v.type_info;
   }

    Variable::Variable(const Variable &v) {
        copy(v);
    }

    Variable::Variable(Variable &&v) {
        copy(v);
    }

    Variable &Variable::operator=(const Variable &v) {
        copy(v);
        return *this;
    }

    Variable &Variable::operator=(Variable &&v) {
        copy(v);
        return *this;
    }

    Variable::Variable(double d) {
        val.fval = d;
        type = VAR_CONST;
        type_info = VAR_DOUBLE;
    }

    Variable::Variable(const std::string &s) : value{s} {
        val.fval = 0;
        type = VAR_CONST;
        type_info = VAR_STRING;
    }

    Variable::Variable(const std::string &n, const std::string &v) : name{n}, value{v} {
        val.fval = 0;
        type = VAR_VAR;
    }

    Variable::Variable(const std::string &n, VAR_TYPE_INFO t) : name{n} {
        val.fval = 0;
        type = VAR_VAR;
        type_info = t;
    }
    
    Variable::Variable(const std::string &n, VAR_TYPE t, VAR_TYPE_INFO vt) : name{n}, type{t}, type_info{vt} {
        val.fval = 0;
    }

    Variable::Variable(const std::string &n, const double &d) : name{n}, type{VAR_VAR}, type_info{VAR_DOUBLE} {
        val.fval = d;
    }


    SymbolTable::SymbolTable() : index{0} {

    }

    
    void SymbolTable::enter(std::string name, std::string value) {
        data[name].name = name;
        data[name].value = value;
        if(data[name].index == -1)
            data[name].index = index++;
    }

    void SymbolTable::enter(std::string name, std::string value, int i) {
        data[name].name = name;
        data[name].value = value;
        if(data[name].index == -1)
            data[name].index = i;
        data[name].id = true;
    }


    void SymbolTable::enter(std::string name, double value) {
        data[name].name = name;
        data[name].val.fval = value;
        if(data[name].index == -1)
            data[name].index = index++;

    }
    void SymbolTable::enter(std::string name, long value) {
        data[name].name = name;
        data[name].val.lval = value;
        if(data[name].index == -1)
            data[name].index = index++;
    }

    void SymbolTable::enter_const(std::string text) {
        const_strings.push_back(text);
    }

    long &SymbolTable::getInteger(std::string name) {

       if(data.find(name) == data.end() && parent != nullptr)
            return parent->getInteger(name);

        return data[name].val.lval;
    }
  
    double &SymbolTable::getDouble(std::string name) {
        if(data.find(name) == data.end() && parent != nullptr)
            return parent->getDouble(name);

        return data[name].val.fval;
    }
    std::string &SymbolTable::getString(std::string name) {

        if(data.find(name) == data.end() && parent != nullptr)
            return parent->getString(name);

        return data[name].value;
    }

    int SymbolTable::getIndex(std::string name) {
        return data[name].index;
    }

    void SymbolTable::print() {
        std::cout << "Symobl Table: " << name << ":\n";
        for(auto &i : data) {
            std::cout << ((i.second.id == true) ? "global identiifer: " : "variable: ") << i.first << " = " << i.second.val.fval << ":" << i.second.value << "\n";
        }
        if(parent != nullptr)
            parent->print();       
    }

    bool SymbolTable::valid(std::string name) {
        auto it = data.find(name);
        if(it != data.end() && it->second.id == false)
            return true;
        if(parent != nullptr)
            return parent->valid(name);
        return false;
    }

    Variable &SymbolTable::getVar(const std::string &name) {
        return data[name];
    }
    
}