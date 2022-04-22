#include"scan_lex.hpp"

namespace scan {

    void crunch(Scanner *scan, std::ostream &out) {
        Token token;
        int index = 0;
        while(scan->nextToken(token)) {
            if(token.keyword != KEY_EMPTY) {
                out.write("$", sizeof('$'));
                out.write(reinterpret_cast<char*>(&token.keyword), sizeof(token.keyword));
            } else if(token.oper != OP_EMPTY) {
                out.write("@", sizeof('@'));
                out.write(reinterpret_cast<char*>(&token.oper), sizeof(token.oper));
            } else if(token.type == TOKEN_ID) { 
                out.write("~", sizeof('~')); 
                int in = scan->table.getIndex(token.token);
                out.write(reinterpret_cast<char*>(&in), sizeof(in));
            } else if(token.type == TOKEN_STRING) {
                out.write("#", sizeof('#'));
                out.write(reinterpret_cast<char*>(&index), sizeof(index));
                index ++;
            }
            else if(token.type == TOKEN_NUMBER) {
                out.write("&", sizeof('&'));
                double val = atof(token.token.c_str());
                out.write(reinterpret_cast<char*>(&val), sizeof(val));
            }
        }
        out.write("!", sizeof('!'));
        int ts = scan->table.const_strings.size();
        out.write(reinterpret_cast<char*>(&ts), sizeof(ts));
        for(int i = 0; i < scan->table.const_strings.size(); ++i) {
            int length = scan->table.const_strings[i].length();
            out.write(reinterpret_cast<char*>(&length), sizeof(length));
            out.write(scan->table.const_strings[i].c_str(), length);
        }
        out.write("^", sizeof('^'));
        int sz = scan->table.data.size();
        out.write(reinterpret_cast<char*>(&sz), sizeof(sz));
        for(auto it = scan->table.data.begin(); it != scan->table.data.end(); it++) {
            int len = it->first.length();
            out.write(reinterpret_cast<char*>(&len), sizeof(len));
            out.write(it->first.c_str(), len);
            int index = it->second.index;
            out.write(reinterpret_cast<char*>(&index), sizeof(index));
        }
    }
    void uncrunch(std::istream &in) {
        char c = 0;
        while(!in.eof()) {
            in.read(reinterpret_cast<char*>(&c), sizeof(c));
            switch(c) {
                case '$': {
                   KEYWORD_TYPES keyword;
                   in.read(reinterpret_cast<char*>(&keyword), sizeof(keyword));
                   std::cout << keywords[keyword] << "\n";
                }
                break; 
                case '@': {
                    OP_TYPES op;
                    in.read(reinterpret_cast<char*>(&op), sizeof(op));
                    std::cout << operators[op] << "\n";
                }
                break; 
                case '~': {
                    int index;
                    in.read(reinterpret_cast<char*>(&index), sizeof(index));
                    std::cout << "~" << index << "\n";
                }
                break;
                case '#': {
                    int index;
                    in.read(reinterpret_cast<char*>(&index), sizeof(index));
                    std::cout << "#" << index << "\n";
                }
                break;
                case '&': {
                    double d;
                    in.read(reinterpret_cast<char*>(&d), sizeof(d));
                    std::cout << d << "\n";
                }
                break;
                case '!': {
                    int ts = 0;
                    in.read(reinterpret_cast<char*>(&ts), sizeof(ts));
                    for(int i = 0; i < ts; ++i) {
                        int len = 0;
                        in.read(reinterpret_cast<char*>(&len), sizeof(len));
                        char *buf = new char [len + 1];
                        in.read(buf, len);
                        buf[len] = 0;
                        std::string text = buf;
                        delete [] buf;
                        std::cout << i << ": " << text << "\n";                       
                    }
                }
                break;
                case '^': {
                    int sz = 0;
                    in.read(reinterpret_cast<char*>(&sz), sizeof(sz));
                    for(int i = 0; i < sz; ++i) {
                        int len = 0;
                        in.read(reinterpret_cast<char*>(&len), sizeof(len));
                        char *buf;
                        buf = new char [len+1];
                        in.read(buf, len);
                        buf[len] = 0;
                        std::string text = buf;
                        delete [] buf;
                        int index;
                        in.read(reinterpret_cast<char*>(&index), sizeof(index));
                        std::cout << index << ": " << text << "\n";
                    }
                }
                break; 
            }
        }
    }


}