#ifndef _SCAN_TOKEN_H_
#define _SCAN_TOKEN_H_

#include<iostream>
#include<string>


namespace scan {

    class Scanner;

    enum TOKEN_TYPE { TOKEN_NULL, TOKEN_STRING, TOKEN_ID, TOKEN_NUMBER, TOKEN_SYMBOL, TOKEN_CHAR, TOKEN_WHITESPACE, TOKEN_COMMENT, TOKEN_KEYWORD };
    static const char *keywords[] = {"proc", "let", "if", "else","elif","for", "while", "call", "match","print", 0};
    enum KEYWORD_TYPES{ KEY_PROC=0, KEY_LET, KEY_IF, KEY_ELSE, KEY_ELIF, KEY_FOR, KEY_WHILE, KEY_CALL, KEY_MATCH,KEY_PRINT,KEY_EMPTY };
    static const char *operators[] = { "!", "@", "$", "%", "^", "&", "*", "(", ")", "-", "+", "--", "++", ">>", "<<", "==", "!=", "+=", "-=", "*=", "&=", "|=","^=","%=","&&", "||", "<", ">", "[", "]", "{", "}", ".", ",", ":", ";", "=", 0};
    enum OP_TYPES { OP_NOT=0, OP_AT, OP_DOLLAR, OP_MOD,OP_XOR,OP_AND,OP_MUL, OP_OP, OP_CP, OP_MINUS, OP_PLUS, OP_MINUS_MINUS, OP_PLUSPLUS, OP_SHIFT_RIGHT, OP_SHIFT_LEFT, OP_EQ_EQ, OP_NE, OP_PE, OP_MINE, OP_ME, OP_AE, OP_OE, OP_XE, OP_MOD_E, OP_AND_AND, OP_OR_OR,OP_LESS, OP_GREATER, OP_BRACE_O, OP_BRACE_C, OP_BLOCK_O, OP_BLOCK_C, OP_DOT, DOT_COMMA, OP_COLON, OP_SEMI_COLON, OP_EQUAL, OP_EMPTY };
    class Token {
    public:
        Token();
        Token(const Token &type);
        Token(Token &&type);
        Token(const std::string &t, TOKEN_TYPE type, int line);

        Token &operator=(const Token &type);
        Token &operator=(Token &&type);
        Token &operator=(const std::string &t);

        bool operator==(const Token &ty);
        friend std::ostream &operator<<(std::ostream &out, const Token &ty);
        KEYWORD_TYPES lookupKeyword(const std::string &text);
        OP_TYPES lookupOperator(const std::string &text);
        friend class Scanner;
    protected:
        std::string token;
        TOKEN_TYPE type;
        KEYWORD_TYPES keyword;
        OP_TYPES oper;
        int lineno;
    };
}

#endif