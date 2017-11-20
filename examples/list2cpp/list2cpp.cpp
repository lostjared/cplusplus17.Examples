#include "list2cpp.hpp"
#include<iomanip>

namespace lst {
    
    OutputList::OutputList(const OutputList &l) : items(l.items), skip_lines(l.skip_lines) {
        
    }
    OutputList::OutputList(OutputList &&l) : items(std::move(l.items)), skip_lines(l.skip_lines) {
        
    }
    OutputList& OutputList::operator=(OutputList &l) {
        items = l.items;
        return *this;
    }
    
    OutputList& OutputList::operator=(OutputList &&l) {
        items = std::move(l.items);
        return *this;
    }
    
    std::string OutputList::escapeSequence(const std::string &s) {
        std::string temp;
        for(std::size_t i = 0; i < s.length(); ++i) {
            if(s[i] == '\"' || s[i] == '\\') {
                temp += "\\";
                temp += s[i];
            } else {
                temp += s[i];
            }
        }
        return temp;
    }
    
    bool OutputList::validName(const std::string &s) {
        if(s.length() == 0) return false;
        if(isdigit(s[0])) {
            return false;
        }
        for(unsigned int i = 0; i < s.length(); ++i) {
            if (!isdigit(s[i]) && !isalpha(s[i]) && s[i] != '_') {
                return false;
            }
        }
        return true;
    }
    
    
    void OutputList::addItem(std::string type) {
        items.push_back(type);
    }
    
    bool OutputList::addFile(std::string name) {
        std::fstream file;
        if(file.open(name, std::ios::in); !file.is_open()) {
            std::cerr << "Error: could not open file...\n";
            return false;
        }
        addStream(file);
        file.close();
        return true;
    }
    
    bool OutputList::addStream(std::istream &file) {
        while(!file.eof()) {
            std::string value;
            std::getline(file, value);
            if(file) {
                if(skip_lines == true) {
                    if(value.length()>0)
                        items.push_back(value);
                    
                } else {
                    items.push_back(value);
                }
            }
        }
        return true;
    }
    
    void OutputList::sort(bool greater) {
        if(greater == true)
        	std::sort(items.begin(), items.end(), std::greater<std::string>());
        else
            std::sort(items.begin(), items.end(), std::less<std::string>());
    }
    
    bool OutputList::outputToFile(std::ostream &file, std::string varname, ListType type) {
        file << "#ifndef __LIST2CPP_" << varname << "\n";
        file << "#define __LIST2CPP_" << varname << "\n";
        switch(type) {
            case ListType::STRING:
                outputToFileAsString(file, varname);
                break;
            case ListType::CHAR:
                outputToFileAsChar(file, varname);
                break;
            case ListType::BINARY:
                outputToFileAsBinary(file, varname);
                break;
        }
        file << "\n\n#endif\n\n";
        return true;
    }
    
    bool OutputList::outputToFile(std::string filename,std::string varname,ListType type) {
        std::fstream file;
        if(file.open(filename, std::ios::out); !file.is_open()) {
            std::cerr << "Error: could not open output file...\n";
            return false;
        }
        outputToFile(file, varname, type);
        file.close();
        return true;
    }
    
    void OutputList::outputToFileAsBinary(std::ostream &file, std::string varname) {
        unsigned long len = 0;
        for(unsigned int i = 0; i < items.size(); ++i) {
            len += items[i].length();
            len++;
        }
        len++;
        file << "\ninline constexpr unsigned long " << varname << "_size = " << len << ";\n";
        file << "inline constexpr unsigned char " << varname << "_arr[" << varname << "_size" << "] = {\n";
         unsigned int counter = 0;
         for(unsigned int i = 0; i < items.size(); ++i) {
            for(unsigned int z = 0; z  < items[i].length(); ++z) {
                std::string temp;
                unsigned int value = static_cast<unsigned int>(static_cast<unsigned char>(items[i][z]));;
                file << "0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << value << ", ";
                ++counter;
                if((counter%10)==0) file << "\n";
            }
            file << "0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<unsigned int>('\n') << ", ";
            ++counter;
            if((counter%10)==0) file << "\n";
        }
        file << "0 };\n";
    }
    
    void OutputList::outputToFileAsChar(std::ostream &file, std::string varname) {
        file << "inline unsigned long " << varname << "_size = " << size() << ";\n";
        file << "\ninline const char *" << varname << "_arr[] = {";
        for(std::size_t i = 0; i < size(); ++i) {
            if(i > size()-2) {
                file << "\"" << items[i] << "\"\n};\n";
            } else {
                file << "\"" << items[i] << "\",\n";
            }
        }
    }
    
    void OutputList::outputToFileAsString(std::ostream &file, std::string varname) {
        file << "#include<string>\n\n";
        file << "inline unsigned long " << varname << "_size = " << size() << ";\n";
        file << "\n\ninline std::string " << varname << "_arr"  << "[] = {\n";
        for(std::size_t i = 0; i < size(); ++i) {
            if(i > size()-2) {
                file << "\"" << items[i] << "\"\n};\n";
            } else {
                file << "\"" << items[i] << "\",\n";
            }
        }
    }
    

}
