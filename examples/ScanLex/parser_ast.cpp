#include "parser_ast.hpp"

namespace parse {

    using namespace scan;

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
           parseCode();
       } catch(ParserException &e) {
           std::cerr << e.error() << "\n";
           return false;
       }
       return true;
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

  void AST::parseStatement(Body &body) {
      while(token.keyword != KEY_END) {
          if(match(KEY_RETURN)) {
              Statement s;
              s.expression = parseReturn();
              body.statements.push_back(s);
          } else if (match(KEY_LET)) {
              Statement s;
              s.expression = parseLet();
              body.statements.push_back(s);
          } 
          else {
            Statement s;
            s.expression = parseExpr();
            body.statements.push_back(s);
            consume(OP_SEMI_COLON);
          }
      }
      // test
  }

  Expr *AST::parseReturn() {
      consume(KEY_RETURN);
      Expr *e = parseExpr();
      return e;
  }

Expr *AST::parseLet() {
    consume(KEY_LET);
    Expr *e = parseExpr();
    return e;
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
       getToken();
       parseArgs(n->proc.param);
       parseBody(n->proc.body);
       root.children.push_back(n);
     
   }

   Expr *AST::parseExpr() {
       return 0;
   }
        
    Expr *AST::parseComp() {
        return 0;
    }
        
    Expr *AST::parseEqual() {
        return 0;
    }
    
    Expr *AST::parseTerm() {
        return 0;
    }
        
    Expr *AST::parseFactor() {
        return 0;
    }
        
    Expr *AST::parsePrim() {
        return 0;
    }

    bool AST::match(const std::initializer_list<OP_TYPES> &lst) {
        for(auto &i : lst) {
            if(token.oper != i)
                return false;
        }
        return true;
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
           out << "proc: " << n->proc.name << "\n";
           break;
           default:
           break;
       }
        
        for(int i = 0; i < n->children.size(); ++i)
           printTree(out, n->children[i]);
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

