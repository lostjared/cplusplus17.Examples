#include "scan_lex.hpp"

namespace scan {

    Scanner::Scanner(const std::string &input_text) : text{input_text}, lineno{0}, colno{0}, index{0}, token_index{0} { 
        for(int i = 0; i < 0xFF; ++i) {
            char_table[i] = TOKEN_NULL;
        }
        for(int i = 'a'; i <= 'z'; ++i)
            char_table[i] = TOKEN_CHAR;
        for(int i = 'A'; i <= 'Z'; ++i) 
            char_table[i] = TOKEN_CHAR;

        for(int i = '0'; i <= '9'; ++i) 
            char_table[i] = TOKEN_NUMBER;

        const char *szOp = "!@$%^&*()_+=-<>{}|/\\.,[];:";
        for(int i = 0; szOp[i] != 0; ++i) 
            char_table[szOp[i]] = TOKEN_SYMBOL;

        char_table[' '] = TOKEN_WHITESPACE;
        char_table['\t'] = TOKEN_WHITESPACE;
        char_table['\n'] = TOKEN_WHITESPACE;

        char_table['#'] = TOKEN_COMMENT;
        char_table['"'] = TOKEN_STRING;
    }

    char Scanner::getchar() {
        if(index < text.length())
            return text[index++];
        return -1;
    }
    
    char Scanner::peekchar() {
        if(index + 1 < text.length())
            return text[index + 1];
        return -1;
    }

    char Scanner::curchar() {
        return text[index];
    }

    char Scanner::prevchar() {
        if(index -1 >= 0)
        return text[index-1];
        return -1;
    }

    bool Scanner::scan() {
        lineno = 0;
        colno = 0;
        token_index = 0;
        char c;
        while((c = getchar()) != -1) {
            switch(char_table[c]) {
                case TOKEN_CHAR:
                    grabId();
                break;
                case TOKEN_NUMBER:
                    grabNumber();
                break;
                case TOKEN_STRING:
                    grabString();
                break;
                case TOKEN_SYMBOL:
                    grabSymbol();
                break;
                case TOKEN_WHITESPACE:
                if(c == '\n') lineno ++;
                continue;
                case TOKEN_NULL:
                std::cout << "Unknown character: " << c << "\n";
                continue;
                case TOKEN_COMMENT: {
                    do {
                        c = getchar();
                    } while(c != -1 && c != '\n');

                }
                break;
            }
        }
        return true;
    }

    bool Scanner::nextToken(Token &token) {
        if(token_index < tokens.size()) {
            token = tokens[token_index++];
            return true;
        }
        return false;
    }

    void Scanner::reset() {
        token_index = 0;
    }
        
    void Scanner::tokenIndex(int index, Token &token) {
        token = tokens[index];
    }

    void Scanner::print() {
        for(int i = 0; i < tokens.size(); ++i) {
            std::cout << i << ": " << tokens[i] << "\n";
        }
    }

    void Scanner::grabId() {
        char c = prevchar();
        std::string token;
        do {
            token += c;
            c = getchar();
        } while(c != -1 && char_table[c] == TOKEN_CHAR);

        if(c != -1)
            index--;

        tokens.push_back(Token(token, TOKEN_ID, lineno));
        Token &type = tokens[tokens.size()-1];
        if(type.type == TOKEN_ID)
            table.enter(type.token, "");
    }
    
    void Scanner::grabNumber() {
        char c = prevchar();
        std::string token;
        do {
            token += c;
            c = getchar();
        } while(c != -1 && (char_table[c] == TOKEN_NUMBER || c == '.'));

        if(c != -1)
            index--;

        tokens.push_back(Token(token, TOKEN_NUMBER, lineno));
    }
        
    void Scanner::grabSymbol() {
        char c = prevchar();
        std::string token;
        token += c;
        char ch = curchar();

        std::string temp_lookup;
        temp_lookup += c;
        temp_lookup += ch;

        for(int i = 0; operators[i] != 0; ++i)
                if(temp_lookup == operators[i])
                {
                    tokens.push_back(Token(temp_lookup, TOKEN_SYMBOL, lineno));
                    index++;
                    return;
                }

        tokens.push_back(Token(token, TOKEN_SYMBOL, lineno));
    }
        
    void Scanner::grabString() {
        char c = getchar();
        std::string token;
        do {
            token += c;
            if(c == '\\') {
                char ch = getchar();
                if(ch == -1) {
                    std::ostringstream stream;
                    stream << "Error missing closing quote on Line: " << lineno << "\n";
                    throw ScanException(stream.str());
                }
                token += ch;
                continue;
            }
        } while( (c = getchar()) != -1 && (char_table[c] != TOKEN_STRING));

        if(c == -1) {
            std::ostringstream stream;
            stream << "Error: missing closing quote on line: " << lineno;
            throw ScanException(stream.str());
        }

        tokens.push_back(Token(token, TOKEN_STRING,lineno));
        table.enter_const(token);
    }
   
    void Scanner::crunch(std::ostream &out) {
        Token token;
        int index = 0;
        while(nextToken(token)) {
            if(token.keyword != KEY_EMPTY) {
                out << "$" << token.keyword << " ";
            } else if(token.oper != OP_EMPTY) {
                out << "@" << token.oper << " ";
            } else if(token.type == TOKEN_ID) {
                out << "~" << table.getIndex(token.token) << " ";
            } else if(token.type == TOKEN_STRING) {
                out << "$$" << index++ << " ";
            }
            else {
                out << token.token <<  " ";
            }
        }
        std::cout << "\n";
        for(int i = 0; i < table.const_strings.size(); ++i) {
            out<< i << ": " << "\"" << table.const_strings[i] << "\"" << "\n";
        }
    }
}