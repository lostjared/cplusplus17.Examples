#include "parser_ast.hpp"

namespace parse {

    using namespace scan;
    using namespace backend;

    Item::Item() : index{-1}, keyword{KEY_EMPTY}, oper{OP_EMPTY}, type{TOKEN_NULL}{

    }
    Item::Item(KEYWORD_TYPES k) : index{-1}, keyword{k}, oper{OP_EMPTY}, type{TOKEN_KEYWORD} {

    }
    
    Item::Item(OP_TYPES o) : index{-1}, oper{o}, keyword{KEY_EMPTY}, type{TOKEN_SYMBOL} {

    }
    
    Item::Item(std::string i) : index {-1}, oper{OP_EMPTY}, keyword{KEY_EMPTY}, id{i}, type{TOKEN_ID} {

    }
        
    Item::Item(int i) : index_const{i}, keyword{KEY_EMPTY}, oper{OP_EMPTY}, type{TOKEN_STRING} {

    }

    Item::Item(int i, bool) : index{i}, keyword{KEY_EMPTY}, oper{OP_EMPTY}, type{TOKEN_ID}{

    }
        
    Item::Item(double d) : val{d}, keyword{KEY_EMPTY}, oper{OP_EMPTY}, type{TOKEN_NUMBER} {

    }

    Item::Item(const Item &i) {
        copy(i);
    }
    Item::Item(Item &&i) {
        copy(i);
    }
    Item &Item::operator=(const Item &i) {
        copy(i);
        return *this;
    }
    
    Item &Item::operator=(Item && i) {
        copy(i);
        return *this;
    }

    void Item::copy(const Item &i) {
        index = i.index;
        keyword = i.keyword;
        oper = i.oper;
        type = i.type;
        index_const = i.index_const;
        val = i.val;
        id = i.id;
    }

    Function::~Function() {
        for(int i = 0; i < expressions.size(); ++i) {
            Expr *expression = expressions[i];
            if(expression != nullptr)
               delete expression;
        }
    }

    Expr::Expr() {
        left = nullptr;
        right = nullptr;
        group = nullptr;
        func = nullptr;
    }

     Expr::~Expr() {
         if(left != nullptr)
            delete left;
        left = nullptr;
        if(right != nullptr)
            delete right;
        right = nullptr;
        if(group != nullptr)
            delete group;
        group = nullptr;

        if(func != nullptr)
            delete func;
        func = nullptr;
     }

    Statement::Statement() {
        expression = nullptr;
    }

     Statement::~Statement() {
        if(expression != nullptr)
            delete expression;
        expression = nullptr;
     }

     Body::~Body() {}

    AST::AST(std::istream *i) : in{i} {}

    void AST::scan() {
        char c = 0;
        while(!in->eof()) {
            in->read(reinterpret_cast<char*>(&c), sizeof(c));
            switch(c) {
                case '$': {
                   KEYWORD_TYPES keyword;
                   in->read(reinterpret_cast<char*>(&keyword), sizeof(keyword));
                   tokens.push_back(Item(keyword));

                }
                break; 
                case '@': {
                    OP_TYPES op;
                    in->read(reinterpret_cast<char*>(&op), sizeof(op));
                    tokens.push_back(Item(op));
                }
                break; 
                case '~': {
                    int index;
                    in->read(reinterpret_cast<char*>(&index), sizeof(index));
                    tokens.push_back(Item(index, true));
                }
                break;
                case '#': {
                    int index;
                    in->read(reinterpret_cast<char*>(&index), sizeof(index));
                    tokens.push_back(Item(index));
                }
                break;
                case '&': {
                    double d;
                    in->read(reinterpret_cast<char*>(&d), sizeof(d));
                    tokens.push_back(Item(d));
                }
                break;
                case '!': {
                    int ts = 0;
                    in->read(reinterpret_cast<char*>(&ts), sizeof(ts));
                    for(int i = 0; i < ts; ++i) {
                        int len = 0;
                        in->read(reinterpret_cast<char*>(&len), sizeof(len));
                        char *buf = new char [len + 1];
                        in->read(buf, len);
                        buf[len] = 0;
                        std::string text = buf;
                        delete [] buf;
                        const_strings.push_back(text);                     
                    }
                }
                break;
                case '^': {
                    int sz = 0;
                    in->read(reinterpret_cast<char*>(&sz), sizeof(sz));
                    for(int i = 0; i < sz; ++i) {
                        int len = 0;
                        in->read(reinterpret_cast<char*>(&len), sizeof(len));
                        char *buf;
                        buf = new char [len+1];
                        in->read(buf, len);
                        buf[len] = 0;
                        std::string text = buf;
                        delete [] buf;
                        int index;
                        in->read(reinterpret_cast<char*>(&index), sizeof(index));
                        id.enter(text, "", index);
                        identifiers[index] = text;
                        
                    }
                    return;
                }
                break; 
            }
        }
    }

    void AST::print(std::ostream &out) {
        for(int i = 0; i < tokens.size(); ++i) {
            switch(tokens[i].type) {
                case TOKEN_ID:
                out << "id: " << identifiers[tokens[i].index] << "\n";
                break;
                case TOKEN_STRING:
                out << "str: " << const_strings[tokens[i].index_const] << "\n";
                break;
                case TOKEN_KEYWORD:
                out << "keyword: " << keywords[tokens[i].keyword] << "\n";
                break;
                case TOKEN_NUMBER:
                out << "number: " << tokens[i].val << "\n";
                break;
                case TOKEN_SYMBOL:
                out << "operator: " << operators[tokens[i].oper] << "\n";
                break;
                default:
                break;
            }
        }
    }

   bool AST::buildTree() {
       token = tokens[0];
       sindex = 0;
       try {
           cur_table = &id;
           parseCode();
       } catch(ParserException &e) {
           std::cerr << e.error() << "\n";
           return false;
       }
       return true;
   }

    AST::~AST() {
        eraseTree(&root);
    }

   void AST::parseCode() {
       getToken();
       switch(token.type) {
           case TOKEN_KEYWORD:
           switch(token.keyword) {
               case KEY_PROC:
               getToken();
               parseProc();
               parseCode();
               break;
               default:
               break;
           }
           break;
           default:
           break;
       }
   }

  Expr *AST::parseAssignment() {
        if(!cur_table->valid(identifiers[token.index])) {
            std::ostringstream stream;
            stream << "Exception: Variable " << identifiers[token.index] << " not declared!\n";
            throw ParserException(stream.str());
        }
        getToken();
        if(match({OP_EQUAL})) {
            consume(OP_EQUAL);
            Expr *e = parseExpr();
            return e;
         }
        return nullptr;
  }

  void AST::parseStatement(Body &body) {
      while(token.keyword != KEY_END) {
          if(match(KEY_RETURN)) {
              Statement *s = new Statement();
              s->expression = parseReturn();
              s->type = STATE_RETURN;
              body.statements.push_back(s);
          } else if (match(KEY_LET)) {
              Statement *s = new Statement();
              s->expression = parseLet(s);
              s->type = STATE_LET;
              body.statements.push_back(s);
              consume(OP_SEMI_COLON);
          } 
          else if(match(TOKEN_ID) && match_lookahead(OP_EQUAL)) {
             Statement *s = new Statement();
             s->var = identifiers[token.index];
             s->expression = parseAssignment();
             s->type = STATE_ASSIGN;
             body.statements.push_back(s);
          } else {
              getToken();
          }
      }
  }

    Expr *AST::parseReturn() {
      consume(KEY_RETURN);
      Expr *e = parseExpr();
      return e;
    }

    Expr *AST::parseLet(Statement *s) {
        consume(KEY_LET);
        if(match(TOKEN_ID)) {
            cur_table->enter(identifiers[token.index], "");
            s->var = identifiers[token.index];
            if(match_lookahead(OP_EQUAL))
                return parseAssignment();
            else 
                getToken();
        }
        return 0;
    }

    void AST::parseBody(Body &body) {
       if(consume(KEY_BEGIN)) {
           parseStatement(body);
            if(match(KEY_END)) {
               consume(KEY_END);
               consume(OP_SEMI_COLON);
           } else {
               
           }
       }
   }

    void AST::parseArgs(ArgList &args) {
        consume(OP_OP);
        if(match({OP_CP})) { 
            consume(OP_CP);
            return;
        }

        while(token.type == TOKEN_ID) {
            args.args.push_back(identifiers[token.index]);
            getToken();
            if(match({OP_CP})) {
                consume(OP_CP);
                return;
            }
            if(match({OP_COMMA}))
            {
                consume(OP_COMMA);
            }
        }
    }



   void AST::parseProc() {
       std::string name;
       name = identifiers[token.index];
       TreeNode *n = new TreeNode();
       n->proc.name = name;
       n->type = NODE_PROC;
       n->proc.id.parent = &id;
       n->proc.id.name = name;
       cur_table = &n->proc.id;
       proc = &n->proc;
       getToken();
       parseArgs(n->proc.param);
       parseBody(n->proc.body);
       root.children.push_back(n);
   }

   Expr *AST::parseExpr() {
       return parseEqual();
   }
        
    Expr *AST::parseComp() {
        Expr *e = parseTerm();
        while(match({OP_GREATER, OP_LESS, OP_GTE, OP_LTE})) {
            OP_TYPES oper = token.oper;
            getToken();
            Expr *ne = new Expr();
            ne->left = e;
            ne->oper = oper;
            ne->right = parseTerm();
            ne->type = EXPR_BINARY;
            e = ne;
        }
        return e;
    }
        
    Expr *AST::parseEqual() {
        Expr *e = parseComp();
        while(match({OP_EQ_EQ, OP_NE})) {
            OP_TYPES oper = token.oper;
            getToken();
            Expr *ne = new Expr();
            ne->left = e;
            ne->oper = oper;
            ne->right = parseComp();
            ne->type = EXPR_BINARY;
            e = ne;
        }
        return e;
    }
    
    Expr *AST::parseTerm() {
        Expr *e = parseFactor();
        while(match({OP_PLUS, OP_MINUS})) {
            OP_TYPES oper = token.oper;
            getToken();
            Expr *right = parseFactor();
            Expr *ne = new Expr();
            ne->left = e;
            ne->oper = oper;
            ne->right = right;
            ne->type = EXPR_BINARY;
            e = ne;
        }
        return e;
    }
        
    Expr *AST::parseFactor() {
        Expr *e = parseUnary();
        while(match({OP_DIV, OP_MUL})) {
            OP_TYPES oper = token.oper;
            getToken();
            Expr *ne = new Expr();
            ne->left = e;
            ne->oper = oper;
            ne->right = parseUnary();
            ne->type = EXPR_BINARY;
            e = ne;
        }
        return e;
    }
        
    Expr *AST::parsePrim() {
        if(match(TOKEN_ID)||match(TOKEN_NUMBER)||match(TOKEN_STRING)) {

            if(match(TOKEN_ID) && match_lookahead(OP_OP)) {
                Expr *e = new Expr();
                e->left = nullptr;
                e->right = nullptr;
                e->oper = OP_EMPTY;
                e->type = EXPR_FUNC;
                e->func = parseFunction();
                return e;
            } else {

                Expr *e = new Expr();
                e->left = 0;
                e->right = 0;
                e->oper = OP_EMPTY;
                e->type = EXPR_LITERAL;
                e->token = token;
                getToken();
                return e;
            }
        }

        if(match({OP_OP})) {
            getToken();
            Expr *e = parseExpr();
            consume(OP_CP);
            Expr *ne = new Expr();
            ne->group = e;
            ne->type = EXPR_GROUP;
            return ne;
        }
        return 0;
    }

    Expr *AST::parseUnary() {
        if(match({OP_MINUS, OP_NOT})) {
            OP_TYPES oper = token.oper;
            getToken();
            Expr *right = parseUnary();
            Expr *ne = new Expr();
            ne->left = 0;
            ne->oper = oper;
            ne->right = right;
            ne->type = EXPR_UNARY;
            return ne;
        }
        return parsePrim();
    }


    bool AST::match(const std::initializer_list<OP_TYPES> &lst) {
        for(auto &i : lst) {
            if(i == token.oper)
                return true;
        }
        return false;
    }

    bool AST::match(TOKEN_TYPE type) {
        if(token.type == type)
            return true;
        return false;
    }

    bool AST::match_lookahead(OP_TYPES type) {
        if(sindex < tokens.size() && tokens[sindex].oper == type)
            return true;
        return false;
    }

    Item *AST::prev() {
        if(sindex-1 >= 0)
            return &tokens[sindex-1];
        else {
            std::ostringstream stream;
            stream << "Exception: index of token out of range.\n";
            throw ParserException(stream.str());
        }
        return nullptr;
    }


    bool AST::match(KEYWORD_TYPES key) {
        if(token.keyword == key)
            return true;
        return false;
    }


   bool AST::consume(TOKEN_TYPE type) {
       if(token.type == type) {
           getToken();
           return true;
       }
       std::ostringstream stream;
       stream << "Expected: " << type << " found: " << type;
       throw ParserException(stream.str());
       return false;
   }
   bool AST::consume(OP_TYPES type) {
       if(token.oper == type) {
           getToken();
           return true;
       }
       std::ostringstream stream;
       stream << "Expected: " << operators[type] << " found: " << token.type;
       switch(token.type) {
           case TOKEN_SYMBOL:
           stream << " " << operators[token.oper];
           break;
           case TOKEN_ID:
           stream << " " << identifiers[token.index];
           break;
           case TOKEN_KEYWORD:
           stream << " " << keywords[token.keyword];
           break;
           default:
           break;
       }
       throw ParserException(stream.str());
       return false;
   }
   
   bool AST::consume(KEYWORD_TYPES key) {
       if(token.keyword == key) {
           getToken();
           return true;
       }
       std::ostringstream stream;
       stream << "Expected: " << keywords[key] << " found: " << token.type;
       switch(token.type) {
           case TOKEN_SYMBOL:
           stream << " " << operators[token.oper];
           break;
           case TOKEN_ID:
           stream << " " << identifiers[token.index];
           break;
           case TOKEN_KEYWORD:
           stream << " " << keywords[token.keyword];
           break;
           default:
           break;
       }
       throw ParserException(stream.str());
       return false;
   }

   void AST::printTree(std::ostream &out, TreeNode *n) {
       switch(n->type) {
           case NODE_PROC:
           out << "proc: " << n->proc.name << ": " << n->proc.body.statements.size() << " statements\n";
           for(auto &i : n->proc.body.statements) {
               if(i->expression != 0)
                eval(i->expression);
               
                if(!stack.empty()) {
                    Variable val = stack.back();
                    stack.pop_back();
                    std::cout << "Value is: " << val << "\n";
                } else {
                    stack.erase(stack.begin(), stack.end());
                }
                std::cout << "\n";
           }
           n->proc.id.print();
           break;
           default:
           break;
       }
        
        for(int i = 0; i < n->children.size(); ++i)
           printTree(out, n->children[i]);
   }

   Function *AST::parseFunction() {
       if(match(TOKEN_ID)) {
           std::string name = identifiers[token.index];
           getToken();
           consume(OP_OP);
           if(match({OP_CP})) {
               consume(OP_CP);
               Function *f = new Function();
               f->name = name;
               return f;
           } else {
                Function *f = new Function();
                f->name = name;
                bool active = true;
                while(active) {
                    Expr *e = parseExpr();
                    f->expressions.push_back(e);
                    if(match({OP_COMMA})) {
                        consume(OP_COMMA);
                        continue;
                    } else {
                        active = false;
                        break;
                    }
                } 
                consume(OP_CP);
                return f;
           }
        
       } else {
           std::ostringstream stream;
           stream << "Exception: expected identifier found: " << token.type;
           throw ParserException(stream.str());
       }
       return nullptr;
   }

   void AST::eraseTree(TreeNode *n) {
       switch(n->type) {
           case NODE_PROC:
           for(auto &i : n->proc.body.statements) {
               delete i;
           }
           break;
           default:
           break;
       }
        for(int i = 0; i < n->children.size(); ++i)
           eraseTree(n->children[i]);
       
   }


    void AST::parExpr(OP_TYPES oper, Expr *left, Expr *right) {
     
    }
        

    void AST::printExpr(Expr *e) {

        if(e != nullptr) {
            switch(e->type) {
                case EXPR_BINARY:
                if(e->left != nullptr)
                    printExpr(e->left);
                if(e->right != nullptr)
                    printExpr(e->right);

                std::cout << "POP " << operators[e->oper] << "\n";
                
                break;
                case EXPR_FUNC:
                std::cout << "call function: " << e->func->name << "\n";
                break;
                case EXPR_LITERAL:
                switch(e->token.type) {
                    case TOKEN_ID:
                    std::cout << identifiers[e->token.index] << "\n";
                    break;
                    case TOKEN_STRING:
                    std::cout << const_strings[e->token.index_const] << "\n";
                    break;
                    case TOKEN_NUMBER:
                    std::cout << "PUSH(" << e->token.val << ")\n";
                    break;
                    default:
                    break;
                }
                break;
                default:
                case EXPR_GROUP:
                std::cout << "(\n";
                if(e->group != nullptr)
                    printExpr(e->group);
                std::cout << ")";
                break;
                break;
            }
        }
   }

   void AST::eval(Expr *e) {
        if(e != nullptr) {
            switch(e->type) {
                case EXPR_BINARY: {

                    if(e->left != nullptr)
                        eval(e->left);
                    if(e->right != nullptr)
                        eval(e->right);

                    Variable op1 = stack.back();
                    stack.pop_back();
                    Variable op2 = stack.back();
                    stack.pop_back();
                    switch(e->oper) {
                    case OP_PLUS:
                        bend.put(Inc(O_ADD, op1, op2));
                    break;
                    case OP_MINUS:
                        bend.put(Inc(O_SUB, op1, op2));
                    break;
                    case OP_MUL:
                        bend.put(Inc(O_MUL, op1, op2));
                    break;
                    case OP_DIV:
                        bend.put(Inc(O_DIV,op1, op2));
                    break;
                    default:
                    break;
                }                

            }
            break;
             case EXPR_FUNC: {
                 if(e->func != nullptr) {
                     for(int i = 0; i < e->func->expressions.size(); ++i) {
                         Expr *expression = e->func->expressions[i];
                        if(expression != nullptr)
                            eval(expression);
                     }
                    bend.put(Inc(O_CALL, Variable(e->func->name), Variable(double(e->func->expressions.size()))));
                 }
             }
            break;
            case EXPR_LITERAL:
                switch(e->token.type) {
                    case TOKEN_ID:
                    std::cout << identifiers[e->token.index] << "\n";
                    stack.push_back(Variable(identifiers[e->token.index], ""));
                    bend.put(Inc(O_PUSH, Variable(identifiers[e->token.index], ""), Variable()));
                    break;
                    case TOKEN_STRING:
                    std::cout << const_strings[e->token.index_const] << "\n";
                    bend.put(Inc(O_PUSH, Variable(const_strings[e->token.index_const]), Variable()));
                    break;
                    case TOKEN_NUMBER:
                    stack.push_back(Variable(e->token.val));
                    bend.put(Inc(O_PUSH, Variable(e->token.val), Variable()));
                    break;
                    default:
                    break;
                }
                break;
                default:
                case EXPR_GROUP:
                if(e->group != nullptr)
                    eval(e->group);
                break;
                break;
            }
        }
   }

   void AST::buildBackend(TreeNode *n) {
    switch(n->type) {
           case NODE_PROC:
           for(auto &i : n->proc.body.statements) {
               switch(i->type) {
                   case STATE_LET: {
                       bend.decl(i->var, "");
                        if(i->expression != 0)
                        eval(i->expression);   
                        bend.put(Inc(O_ASSIGN, Variable(i->var, ""), Variable()));                        
                   }
                   break;
                   case STATE_ASSIGN:
                   bend.decl(i->var, "");
                   if(i->expression != 0)
                        eval(i->expression);
                   bend.put(Inc(O_ASSIGN, Variable(i->var, ""), Variable()));
                   break;
                   default:
                   break;
               }
           }
           n->proc.id.print();
           break;
           default:
           break;
       }
        
        for(int i = 0; i < n->children.size(); ++i)
        buildBackend(n->children[i]);
   }

   void AST::printBackend(std::ostream &out) {
       bend.print(out);
   }

   void AST::run() {
       bend.go();
   }

   TreeNode *AST::rootNode() {
       return &root;
   }


    bool AST::getToken() {
        if(sindex < tokens.size()) {
            token = tokens[sindex++];
            return true;
        }
        return false;
    }
}

