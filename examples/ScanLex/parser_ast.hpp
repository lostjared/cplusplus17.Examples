#ifndef _PARSER_AST_H__
#define _PARSER_AST_H__

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<initializer_list>
#include"scan_lex.hpp"
#include"parser_exception.hpp"

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

    enum EXPR_TYPE { EXPR_LITERAL, EXPR_ID, EXPR_SYMBOL, EXPR_FUNC, EXPR_BINARY, EXPR_RETURN, EXPR_UNARY,EXPR_GROUP,EXPR_EMPTY };

    struct Expr {
        OP_TYPES oper;
        Expr *left, *right;
        Expr *group;
        Item token;
        EXPR_TYPE type;
    };

    enum STATEMENT_TYPE { STATE_LET, STATE_ASSIGN, STATE_FUNC, STATE_RETURN, STATE_EXPR, STATE_EMPTY };

    struct Statement {
        Expr *expression = nullptr;
        STATEMENT_TYPE type = STATE_EMPTY;
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

    enum NODE_TYPE { NODE_ROOT, NODE_PROC, NODE_LET };

    struct TreeNode {
        /// items
        Procedure proc;
        NODE_TYPE type;
        std::vector<TreeNode *> children;
    };

    class AST {
    public:
        explicit AST(std::istream *i);
        void scan();
        void print(std::ostream &out);
        void printTree(std::ostream &out, TreeNode *n);
        bool buildTree();
        bool getToken();
        void parseProc();
        void parseArgs(ArgList &args);
        void parseStatement(Body &body);
        void parseBody(Body &body);
        void parseCode();
        TreeNode *rootNode();
        Expr *parseExpr();
        Expr *parseComp();
        Expr *parseEqual();
        Expr *parseTerm();
        Expr *parseFactor();
        Expr *parsePrim();
        Expr *parseReturn();
        Expr *parseLet();
        Expr *parseUnary();
        bool match(const std::initializer_list<OP_TYPES> &lst);
        bool match(KEYWORD_TYPES key);
        bool match(TOKEN_TYPE type);
        bool consume(KEYWORD_TYPES key);
        bool consume(TOKEN_TYPE type);
        bool consume(OP_TYPES type);
        Item *prev();
        void printExpr(Expr *e);
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