#ifndef _PARSER_AST_H__
#define _PARSER_AST_H__

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include"scan_lex.hpp"

namespace parse {

    using namespace scan;

    struct Item {
        KEYWORD_TYPES keyword;
        OP_TYPES oper;
        std::string id;
        TOKEN_TYPE type;
        int index = -1;
        int index_const = -1;
        double val = 0;

        Item();
        Item(KEYWORD_TYPES key);
        Item(OP_TYPES oper);
        Item(std::string id);
        Item(int index);
        Item(int index, bool);
        Item(double d);

        Item(const Item &i);
        Item(Item &&i);
        Item &operator=(const Item &i);
        Item &operator=(Item && i);

        void copy(const Item &i);
    };

    struct Statement {
    };

    struct Body {
        std::vector<Statement> statements;
    };

    struct ArgList {
        std::vector<std::string> args;
    };

    struct Procedure {
        std::string name;
        Body body;
        ArgList param;

    };
    struct TreeNode {
        /// items
        Procedure proc;
        std::vector<TreeNode *> children;
    };

    class AST {
    public:
        explicit AST(std::istream *i);
        void scan();
        void print(std::ostream &out);
        bool buildTree();
        bool getToken();
    protected:
        std::istream *in;
        std::vector<Item> tokens;
        std::vector<std::string> const_strings;
        std::unordered_map<int, std::string> identifiers;
        scan::SymbolTable id;
        Item token;
        int sindex;
        TreeNode root;
    };
}


#endif