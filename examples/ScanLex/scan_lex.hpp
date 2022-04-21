#ifndef _SCAN_LEX_H__
#define _SCAN_LEX_H__

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include"scan_token.hpp"
#include"scan_exception.hpp"
#include"scan_symbol.hpp"
#include"scan_crunch.hpp"

namespace scan {

    class Scanner {
    public:
        explicit Scanner(const std::string &input_text);
        bool scan();
        char getchar();
        char peekchar();
        char curchar();
        char prevchar();
        void print();
        bool nextToken(Token &token);
        void reset();
        void tokenIndex(int index, Token &token);
        void crunch(std::ostream &out);
        friend void crunch(Scanner *scan, std::ostream &out);
    protected:
        SymbolTable table;
        std::vector<Token> tokens;
        std::string text;
        int lineno;
        int colno;
        int index;
        char char_table[0xFF+1];
        int token_index;
        void grabId();
        void grabNumber();
        void grabSymbol();
        void grabString();
       
    };
}

#endif