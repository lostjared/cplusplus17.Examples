#ifndef _PARSER_H__
#define _PARSER_H__


#include "scan_lex.hpp"
#include "parser_exception.hpp"

namespace parse {

    using namespace scan;

    class Parser {
    public:
        explicit Parser(Scanner *scanner);
        bool checkSyntax();
        bool getToken();
        bool match(TOKEN_TYPE type);
        bool match(KEYWORD_TYPES keyword);
        bool match(OP_TYPES op);

    protected:
        Scanner *scan;
        Token token;
        void parseProcedure();
        void parseArglist();
        void parseBody();
        void parseStatement();
        void parseExpr();
        void parseTerm();
        void parsePrim();
        void parseCall();

    };
}

#endif