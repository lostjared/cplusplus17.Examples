#include"scan_token.hpp"

namespace scan {
 
    Token::Token() : keyword{KEY_EMPTY}, lineno{0}, type{TOKEN_NULL},oper{OP_EMPTY} {

    }
    
    Token::Token(const Token &ty) : token{ty.token}, type{ty.type}, lineno{ty.lineno},keyword{ty.keyword}, oper{ty.oper} {}
        
    Token::Token(Token &&ty) : token{ty.token}, type{ty.type}, lineno{ty.lineno},keyword{ty.keyword}, oper{ty.oper} {}
        
    Token::Token(const std::string &t, TOKEN_TYPE ty, int line) : token{t}, type{ty}, lineno{line},keyword{KEY_EMPTY}, oper{OP_EMPTY}  {
        if(ty == TOKEN_ID) {
            KEYWORD_TYPES key = lookupKeyword(t);
            if(key != KEY_EMPTY) {
                type = TOKEN_KEYWORD;
            }
            keyword = key;
        } else if(ty == TOKEN_SYMBOL) {
            OP_TYPES otype = lookupOperator(t);
            if(otype != OP_EMPTY)
                oper = otype;
        }
    }

    Token &Token::operator=(const Token &ty) {
        token = ty.token;
        type = ty.type;
        lineno = ty.lineno;
        keyword = ty.keyword;
        oper = ty.oper;
        return *this;
    }
    Token &Token::operator=(Token &&ty) {
        token = ty.token;
        type = ty.type;
        lineno = ty.lineno;
        keyword = ty.keyword;
        oper = ty.oper;
        return *this;
    }
    Token &Token::operator=(const std::string &t) {
        token = t;
        return *this;
    }

    bool Token::operator==(const Token &ty) {
        if(token == ty.token && type == ty.type)
        return true;
        return false;
    }

    KEYWORD_TYPES Token::lookupKeyword(const std::string &text) {
        for(int i = 0; keywords[i] != 0; ++i) {
            if(text == keywords[i])
                return KEYWORD_TYPES(i);
        }
        return KEY_EMPTY;
    }

    OP_TYPES Token::lookupOperator(const std::string &text) {
        for(int i = 0; operators[i] != 0; ++i)
            if(text == operators[i])
                return OP_TYPES(i);

        return OP_EMPTY;
    }

    std::ostream &operator<<(std::ostream &out, const Token &ty) {
       out << "Token Line[" << ty.lineno << "] -> : " << ty.token << " Type: " << ty.type;
       return out;
   }
}