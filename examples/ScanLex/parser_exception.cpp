#include "parser_exception.hpp"


namespace parse {
        ParserException::ParserException(const std::string &text) : etext{text} {}
        
        std::string ParserException::error() {
            return etext;
        }
}