#ifndef __LIST2CPP__H_
#define __LIST2CPP__H_
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cctype>

namespace lst {
    enum class ListType { STRING, CHAR };
    class OutputList {
    public:
        OutputList() = default;
        OutputList(const OutputList &l);
        OutputList(OutputList &&);
        OutputList& operator=(OutputList &);
        OutputList& operator=(OutputList &&);
        void addItem(std::string item);
        bool addFile(std::string filename);
        bool addStream(std::istream &in);
        std::size_t size() const { return items.size(); }
        bool outputToFile(std::string filename, std::string varname, ListType type);
        bool outputToFile(std::ostream &file, std::string varname, ListType type);
        bool validName(const std::string &s);
    private:
        std::vector<std::string> items;
        std::string escapeSequence(const std::string &s);
    };
}
#endif

