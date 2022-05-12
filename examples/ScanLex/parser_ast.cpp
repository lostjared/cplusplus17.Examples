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

        if(body != nullptr)
            delete body;

        body = nullptr;
        //std::cout << "deleted expression\n";
     }

    Statement::Statement() {
        expression = nullptr;
    }

     Statement::~Statement() {
        if(expression != nullptr)
            delete expression;
        expression = nullptr;
     }

    Body::~Body() {
        for(int i = 0; i < statements.size(); ++i) {
            Statement *s = statements[i];
            if(s != nullptr) {
                delete s;
                s = nullptr;
            }
        }
    }

   Procedure::Procedure() {

   }
        
  Procedure::~Procedure() {
      for(int i = 0; i < body.size(); ++i) {
          Body *b = body[i];
          if(b != nullptr)
            delete b;
      }
  }

  TreeNode::~TreeNode() {
      for(int i = 0; i < children.size(); ++i) {
          TreeNode *n = children[i];
          delete n;
          n = nullptr;
      }
  }

    AST::AST(std::istream *i) : in{i} {}

    bool AST::scan() {
        char c = 0;
        char header[5];
        in->read(header, 4);
        header[4] = 0;
        if(std::string(header) != "!MXE") {
            return false;
        }
        
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
                    return true;
                }
                break; 
            }
        }
        return true;
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
         } else if(match({OP_STRING_EQUAL})) {
             consume(OP_STRING_EQUAL);
             Expr *e = parseExpr();
             return e;
         }
        return nullptr;
    }

   


    Expr *AST::parseStringAssignment() {

        return nullptr;
    }

  void AST::parseStatement(Body *body) {
      while(token.keyword != KEY_END) {
          if(token.oper == OP_BLOCK_C) {
              return;
          }
          if(match(KEY_RETURN)) {
              Statement *s = new Statement();
              s->expression = parseReturn();
              s->type = STATE_RETURN;
              body->statements.push_back(s);
          } else if (match(KEY_LET)) {
              Statement *s = new Statement();
              s->expression = parseLet(s);
              s->type = STATE_LET;
              body->statements.push_back(s);
              consume(OP_SEMI_COLON);
          } else if(match(KEY_IF)) {

                getToken();
          } else if(match(KEY_WHILE)) {
              Statement *s = new Statement();
              s->type = STATE_WHILE;
              consume(KEY_WHILE);
              consume(OP_OP);
              Expr *e = parseExpr();
              consume(OP_CP);
              Body *b = parseBlock();
              e->body = b;
              s->expression = e;
              body->statements.push_back(s);
          }
          else if(match(TOKEN_ID) && match_lookahead(OP_EQUAL)) {
             Statement *s = new Statement();
             s->var = identifiers[token.index];
             s->expression = parseAssignment();
             s->type = STATE_ASSIGN;
            body->statements.push_back(s);
          } else if(match(TOKEN_ID) && match_lookahead(OP_OP)) {
              Statement *s = new Statement();
              s->var = identifiers[token.index];
              s->expression = parseExpr();
              s->type = STATE_FUNC;
              body->statements.push_back(s);
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
            if(match_lookahead(OP_EQUAL)) {
                s->var_type = VAR_DOUBLE;
                return parseAssignment();
            }
            else if(match_lookahead(OP_STRING_EQUAL)) {
                s->var_type = VAR_STRING;
                return parseAssignment();
            } else
                getToken();
        }
        return 0;
    }

    Body *AST::parseBody(Body *body) {
       if(consume(KEY_BEGIN)) {
           parseStatement(body);
            if(match(KEY_END)) {
               consume(KEY_END);
               consume(OP_SEMI_COLON);
           } else {
               
           }
       }
       return body;
   }

   Body *AST::parseBlock() {
       Body *body = new Body();
       consume(OP_BLOCK_O);
       parseStatement(body);
       //if(match({OP_BLOCK_C})) {
           consume(OP_BLOCK_C);
       //}
       return body;
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
       // while(b) body.push_back(b)
       Body *b = new Body();
       b = parseBody(b);
       proc->body.push_back(b);
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
   }


    void AST::parExpr(OP_TYPES oper, Expr *left, Expr *right) {
     
    }
        

    void AST::printExpr(Expr *e) {

   }

   void AST::eval(Expr *e) {
        if(e != nullptr) {
            switch(e->type) {
                case EXPR_BINARY: {

                    if(e->left != nullptr)
                        eval(e->left);
                    if(e->right != nullptr)
                        eval(e->right);
                    
                    switch(e->oper) {
                    case OP_PLUS:
                        bend.put(Inc(O_ADD, Variable(), Variable()));
                    break;
                    case OP_MINUS:
                        bend.put(Inc(O_SUB, Variable(), Variable()));
                    break;
                    case OP_MUL:
                        bend.put(Inc(O_MUL, Variable(), Variable()));
                    break;
                    case OP_DIV:
                        bend.put(Inc(O_DIV,Variable(), Variable()));
                    break;
                    case OP_EQ_EQ:
                        bend.put(Inc(O_EE,Variable(),Variable()));
                    break;
                    case OP_NE:
                        bend.put(Inc(O_NE,Variable(),Variable()));
                    break;
                    case OP_LTE:
                        bend.put(Inc(O_LTE,Variable(),Variable()));
                    break;
                    case OP_LESS:
                        bend.put(Inc(O_LT,Variable(),Variable()));
                    break;
                    case OP_GREATER:
                        bend.put(Inc(O_GT,Variable(),Variable()));
                    break;
                    case OP_GTE:
                        bend.put(Inc(O_GTE,Variable(),Variable()));
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
                    bend.put(Inc(O_CALL, Variable(e->func->name, VAR_FUNC_NAME, VAR_STRING), Variable(double(e->func->expressions.size()))));
                 }
             }
            break;
            case EXPR_LITERAL:
                switch(e->token.type) {
                    case TOKEN_ID:
                    bend.put(Inc(O_PUSH, Variable(identifiers[e->token.index], VAR_DOUBLE), Variable()));
                    break;
                    case TOKEN_STRING:
                    bend.put(Inc(O_PUSH, Variable(const_strings[e->token.index_const]), Variable()));
                    break;
                    case TOKEN_NUMBER:
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

  void AST::buildBackendBody(Body *body) {
      for(auto &i : body->statements) {
            switch(i->type) {
                case STATE_LET: {
                   switch(i->var_type) {
                        case VAR_DOUBLE:
                            bend.decl(i->var, 0);
                            if(i->expression != 0)
                                eval(i->expression);   
                           bend.put(Inc(O_ASSIGN, Variable(i->var, VAR_DOUBLE), Variable()));                        
                           break;
                        case VAR_STRING:
                            bend.decl(i->var, "");
                           if(i->expression != 0)
                                eval(i->expression);
                           bend.put(Inc(O_SASSIGN, Variable(i->var, VAR_STRING), Variable()));
                           break;
                           default:
                           break;
                       }
                   }
                   break;
                   case STATE_ASSIGN:
                        bend.decl(i->var, "");
                        if(i->expression != 0)
                            eval(i->expression);
                            bend.put(Inc(O_ASSIGN, Variable(i->var, ""), Variable()));

                   break;
                   case STATE_FUNC:
                        eval(i->expression);
                        bend.put(Inc(O_POP, Variable(), Variable()));
                        break;

                    case STATE_WHILE: {
                        static int counter = 0;
                        std::ostringstream stream;
                        stream << "LW" << counter++;
                        std::string label = stream.str();
                        std::string label2;
                        stream << "_OVER";
                        label2 = stream.str();
                        bend.put(Inc(O_LABEL, Variable(label), Variable()));
                        if(i->expression != nullptr)
                            eval(i->expression);
                        bend.put(Inc(O_BNE, Variable(label2), Variable()));
                        if(i->expression != nullptr && i->expression->body != nullptr)
                            buildBackendBody(i->expression->body);
                         bend.put(Inc(O_B, Variable(label), Variable()));
                         bend.put(Inc(O_LABEL, Variable(label2), Variable()));
                    }
                    break;
                   default:
                   break;
                   case STATE_IF:
                   break;
               }
      }
  }

  void AST::buildCode() {
    buildBackend(rootNode());
    
  }

   void AST::buildBackend(TreeNode *n) {

       switch(n->type) {
           case NODE_PROC: {

               for(auto &b : n->proc.body) {
                   buildBackendBody(b);
               }
               if(n->proc.name == "main")
                    bend.put(Inc(O_EXIT, Variable(), Variable()));
           }
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

