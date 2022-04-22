#ifndef __PARSER_EXCEP_H__
#define __PARSER_EXCEP_H__


#include<iostream>
#include<string>

namespace parse {

    class ParserException {
    public:
        ParserException(const std::string &text);
        std::string error();
    protected:
        std::string etext;
    };

}

#endif