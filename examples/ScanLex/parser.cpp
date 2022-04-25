#include"parser.hpp"


namespace parse {
    Parser::Parser(Scanner *scanner) : scan{scanner} {}

    bool Parser::checkSyntax() {
        try {
            while(getToken()) {
                switch(token.type) {
                    case TOKEN_KEYWORD:
                        switch(token.keyword) {
                        case KEY_PROC:
                            parseProcedure();
                        break;
                        case KEY_LET:
                            parseLet();
                            break;
                        default:
                            break;
                    }        
                    break;
                    default:
                        break;
                }
            }
        } catch(ParserException &pe) {
            std::cerr << pe.error() << "\n";
            return false;
        }
        return true;
    }

    void Parser::parseProcedure() {
        getToken();
        match(TOKEN_ID);
        getToken();
        match(OP_OP);
        getToken();
        parseArglist();
        match(OP_CP);
        getToken();
        parseBody();
    }

    void Parser::parseArglist() {

        if(token.oper == OP_AT)
            getToken();   

        while(token.type == TOKEN_ID) {
            match(TOKEN_ID);
            getToken();
            if(token.oper == OP_COMMA)
                getToken();
             if(token.oper == OP_AT)
                getToken();
           
        }
    }
    void Parser::parseBody() {
        match(KEY_BEGIN);
        getToken();
        parseStatement();
        match(KEY_END);
        getToken();
        match(OP_SEMI_COLON);
    }

    void Parser::parseStatement() {
        switch(token.type) {
            case TOKEN_ID: {
                getToken();

                if(token.oper == OP_BRACE_O)
                    parseArray();

                if(token.oper == OP_EQUAL || token.oper == OP_MINE || token.oper == OP_PE || token.oper == OP_AE || token.oper == OP_XE || token.oper == OP_ME || token.oper == OP_MINE || token.oper == OP_DE) {
                    getToken();
                    parseExpr();
                    match(OP_SEMI_COLON);
                    getToken();
                    parseStatement();
                 } else if(token.oper == OP_OP) {
                    getToken();
                    parseCall();
                    match(OP_SEMI_COLON);
                    getToken();
                    parseStatement();
                }
            }
            break;
            case TOKEN_KEYWORD:
            switch(token.keyword) {
                case KEY_RETURN:
                getToken();
                parseExpr();
                match(OP_SEMI_COLON);
                getToken();
                parseStatement();
                    break;
                default:
                    break;
                case KEY_IF:
                parseIf();
                parseStatement();
                    break;
                case KEY_WHILE:
                parseWhile();
                parseStatement();
                    break;
                case KEY_FOR:
                parseFor();
                parseStatement();
                    break;
                case KEY_MATCH:
                parseMatch();
                parseStatement();
                    break;
                case KEY_PRINT:
                getToken();
                parseCall();
                match(OP_SEMI_COLON);
                getToken();
                parseStatement();
                    break;
                case KEY_LET:
                    parseLet();
                    parseStatement();
                    break;
            }
            break;
            default:
            break;
        }
    }

    void Parser::parseExpr() {

        if(token.type == TOKEN_ID) {
            getToken();
            if(token.oper == OP_OP) {
                getToken();
                parseCall();
            }
        }

        if(token.oper == OP_OP)
             getToken();
        
        parsePrim();
        
        if(token.oper == OP_CP)
            getToken();
    }

    void Parser::parseTerm() {

    }

    void Parser::parsePrim() {

        if(token.oper == OP_CP || token.oper == OP_SEMI_COLON)
            return;
        

        switch(token.type) {
            case TOKEN_ID:
            getToken();
            break;
            case TOKEN_NUMBER:
            getToken();
            break;
            case TOKEN_SYMBOL:
            break;
            case TOKEN_STRING:
            getToken();
            break;
            default: {
                std::ostringstream stream;
                stream << "Expected Idenitifer or Number on Line: " << token.lineno << " instead I found: " << token.token;
                throw ParserException(stream.str());
            }
            break;
        }

        if(token.oper == OP_BRACE_O) {
            parseArray();
            parseExpr();
            return;
        } 
        if(token.oper ==  OP_PLUS) {
            getToken();
            parseExpr();
        }
        if(token.oper == OP_MINUS) {
            getToken();
            parseExpr();
        }
        if(token.oper == OP_MUL) {
            getToken();
            parseExpr();
        }
        if(token.oper == OP_DIV) {
            getToken();
            parseExpr();
        }

        if(token.oper == OP_AND || token.oper == OP_XOR || token.oper == OP_OR) {
            getToken();
            parseExpr();
        }
        if(token.oper == OP_AND_AND || token.oper == OP_OR_OR || token.oper == OP_EQ_EQ || token.oper == OP_NE || token.oper == OP_LESS || token.oper == OP_GREATER || token.oper == OP_LTE || token.oper == OP_GTE) {
            getToken();
            parseExpr();
        }
    }

    void Parser::parseCall() {
        parseExpr();
        if(token.oper == OP_COMMA) {
            getToken();
            parseCall();
        } 
    }

    void Parser::parseIf() {
        getToken();
        parseExpr();
        parseBlock();

        if(token.keyword == KEY_ELSE) {
            getToken();
            parseBlock();
        } else if(token.keyword == KEY_ELIF) {
            parseElif();
            if(token.keyword == KEY_ELSE) {
                getToken();
                parseBlock();
            }
        }
    }

    void Parser::parseElif() {
        getToken();
        parseExpr();
        parseBlock();
        if(token.keyword == KEY_ELIF)
            parseElif();
    }


    void Parser::parseWhile() {
        getToken();
        parseExpr();
        parseBlock();
    }
    
    void Parser::parseFor() {
        getToken();
        match(OP_OP);
        getToken();
        match(TOKEN_ID);
        getToken();
        match(OP_COLON);
        getToken();
        match(TOKEN_NUMBER);
        getToken();
        match(OP_COMMA);
        getToken();
        match(TOKEN_NUMBER);
        getToken();
        match(OP_CP);
        getToken();
        parseBlock();
    }

    void Parser::parseMatch() {

    }

    void Parser::parseBlock() {
        match(OP_BLOCK_O);
        getToken();
        parseStatement();
        match(OP_BLOCK_C);
        getToken();
    }

    void Parser::parseArray() {
        match(OP_BRACE_O);
        getToken();
        parseList();
        match(OP_BRACE_C);
        getToken();
    }

    void Parser::parseList() {
        parseExpr();
        if(token.oper == OP_COMMA) {
            getToken();
            parseList();
        }
    }

    void Parser::parseLet() {
        match(KEY_LET);
        getToken();
        match(TOKEN_ID);
        getToken();
        if(token.oper == OP_EQUAL) {
            getToken();
            parseExpr();
        }
        match(OP_SEMI_COLON);
        getToken();
    }

    bool Parser::getToken() {
        if(scan->nextToken(token)) {
            return true;
        }
        return false;
    }

    bool Parser::match(TOKEN_TYPE type) {
        if(token.type == type) return true;
        std::ostringstream stream;
        stream << "Excepted Token: " << type << " found: " << token.token << " on Line: " << token.lineno;
        throw ParserException(stream.str());
        return false;
    }
    
    bool Parser::match(KEYWORD_TYPES keyword) {
        if(token.keyword == keyword) return true;
        std::ostringstream stream;
        stream << "Excepted Keyword: " << keywords[keyword] << " found: " << token.token << " on Line: " << token.lineno;
        throw ParserException(stream.str());
        return false;
    }
    
    bool Parser::match(OP_TYPES op) {
        if(token.oper == op) return true;
        std::ostringstream stream;
        stream << "Excepted Operator: " << operators[op] << " found " << token.token << " on Line: " << token.lineno;
        throw ParserException(stream.str());
        return false;
    }

}