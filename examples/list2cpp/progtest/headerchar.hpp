#ifndef __LIST2CPP_chvar
#define __LIST2CPP_chvar
inline constexpr unsigned long chvar_size = 38;

inline const char *chvar_arr[chvar_size] = {
"#ifndef __LIST2CPP__H_",
"#define __LIST2CPP__H_",
"#include<iostream>",
"#include<string>",
"#include<fstream>",
"#include<vector>",
"#include<algorithm>",
"#include<cctype>",
"",
"namespace lst {",
"    enum class ListType { STRING, CHAR, BINARY};",
"    class OutputList {",
"    public:",
"        OutputList() = default;",
"        OutputList(const OutputList &l);",
"        OutputList(OutputList &&);",
"        OutputList& operator=(OutputList &);",
"        OutputList& operator=(OutputList &&);",
"        void addItem(std::string item);",
"        bool addFile(std::string filename);",
"        bool addStream(std::istream &in);",
"        void sort(bool greater);",
"        std::size_t size() const { return items.size(); }",
"        bool outputToFile(std::string filename, std::string varname, ListType type);",
"        bool outputToFile(std::ostream &file, std::string varname, ListType type);",
"        void outputToFileAsBinary(std::ostream &file, std::string varname);",
"        void outputToFileAsChar(std::ostream &file, std::string varname);",
"        void outputToFileAsString(std::ostream &file, std::string varname);",
"        bool validName(const std::string &s);",
"        void setSkip(bool b) { skip_lines = b; }",
"    private:",
"        std::vector<std::string> items;",
"        std::string escapeSequence(const std::string &s);",
"        bool skip_lines;",
"    };",
"}",
"#endif",
""
};


#endif

