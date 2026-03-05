#include"scan_token.hpp"

namespace scan {
 
    Token::Token() : token{}, type{TOKEN_NULL}, keyword{KEY_EMPTY}, oper{OP_EMPTY}, lineno{0} {

    }
    
    Token::Token(const Token &ty) : token{ty.token}, type{ty.type}, keyword{ty.keyword}, oper{ty.oper}, lineno{ty.lineno} {}
        
    Token::Token(Token &&ty) : token{ty.token}, type{ty.type}, keyword{ty.keyword}, oper{ty.oper}, lineno{ty.lineno} {}
        
    Token::Token(const std::string &t, TOKEN_TYPE ty, int line) : token{t}, type{ty}, keyword{KEY_EMPTY}, oper{OP_EMPTY}, lineno{line}  {
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
        for(std::size_t i = 0; keywords[i] != 0; ++i) {
            if(text == keywords[i])
                return KEYWORD_TYPES(static_cast<int>(i));
        }
        return KEY_EMPTY;
    }

    OP_TYPES Token::lookupOperator(const std::string &text) {
        for(std::size_t i = 0; operators[i] != 0; ++i)
            if(text == operators[i])
                return OP_TYPES(static_cast<int>(i));

        return OP_EMPTY;
    }

    std::ostream &operator<<(std::ostream &out, const Token &ty) {
       out << "Token Line[" << ty.lineno << "] -> : " << ty.token << " Type: " << ty.type;
       return out;
   }

   std::ostream &operator<<(std::ostream &out, TOKEN_TYPE type) {
       switch(type) {
           case TOKEN_CHAR:
                out << "Character";
           break;
           case TOKEN_ID:
                out << "Identifier";
           break;
           case TOKEN_STRING:
                out << "String";
           break;
           case TOKEN_KEYWORD:
                out << "Keyword";
           break;
           case TOKEN_NUMBER:
                out << "Number";
           break;
           case TOKEN_NULL:
                out << "NULL";
           break;
           case TOKEN_SYMBOL:
                out << "Operator";
           break;
           case TOKEN_WHITESPACE:
           case TOKEN_COMMENT:
           break;
       }
       return out;
   }

}