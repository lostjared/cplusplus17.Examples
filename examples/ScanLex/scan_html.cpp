#include"scan_html.hpp"
#include"scan_lex.hpp"

namespace scan {

    std::string convertToHTML(const std::string &text) {
        std::string temp;
        for(int i = 0; i < text.length(); ++i) {
            if(text[i] == ' ')
                temp += "&nbsp;";
            else if(text[i] == '<')
                temp += "&lt;";
            else if(text[i] == '>')
                temp += "&gt;";
            else if(text[i] == '\t')
                temp += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
            else
                temp += text[i];
        }
        return temp;
    }

    void procHTML(std::istream &in, std::ostream &out) {

        out << "<!DOCTYPE html>\n<html>\n<head>\n<title>Debug HTML</title>\n</head>\n<body>\n";
        out << "<table>\n";
        out << "<tr><th>Code</th></tr>";
        out << "<tr><th>Index</th><th>Token</th><th>Type</th></tr>\n";        
        char c = 0;
        int index1 = 1;
        while(!in.eof()) {
            in.read(reinterpret_cast<char*>(&c), sizeof(c));
            switch(c) {
                case '$': {
                   KEYWORD_TYPES keyword;
                   in.read(reinterpret_cast<char*>(&keyword), sizeof(keyword));
                   out << "<tr><th>" << index1 << "</th><th>" << keywords[keyword] << "</th><th>Keyword</th></tr>\n";
                   ++index1;
                }
                break; 
                case '@': {
                    OP_TYPES op;
                    in.read(reinterpret_cast<char*>(&op), sizeof(op));
                    out << "<tr><th>" << index1 << "</th><th>" << convertToHTML(operators[op]) << "</th><th>Operator</th></tr>\n";
                    ++index1;
                }
                break; 
                case '~': {
                    int index;
                    in.read(reinterpret_cast<char*>(&index), sizeof(index));
                    out << "<tr><th>" << index1 << "</th><th>" << index << "</th><th>Identifier</th></tr>\n";
                    ++index1;

                }
                break;
                case '#': {
                    int index;
                    in.read(reinterpret_cast<char*>(&index), sizeof(index));
                    out << "<tr><th>" << index1 << "</th><th>" << index << "</th><th>Const String</th></tr>\n";
                    ++index1;
                }
                break;
                case '&': {
                    double d;
                    in.read(reinterpret_cast<char*>(&d), sizeof(d));
                    out << "<tr><th>" << index1 << "</th><th>" << d << "</th><th>Numeric</th></tr>\n";
                    ++index1;

                }
                break;
                case '!': {
                    out << "</table>";
                    out << "<br><br>";
                    out << "<table>";
                    out << "<tr><th>String Table</th></tr>\n";
                    out << "<tr><th>Index</th><th>String</th></tr>";
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
                        out << "<tr><th>" << i << "</th><th>" << convertToHTML(text) << "</th></tr>";
                    }
                    out << "</table>";
                }
                break;
                case '^': {
                    int sz = 0;
                    out << "<table>";
                    out << "<tr><th>Idenitifer Hash Table</th></tr>";
                    out << "<tr><th>Index</th><th>Identiifer</th></tr>";
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
                        out << "<tr><th>" << index << "</th><th>" << convertToHTML(text) <<"</th></tr>";
                    }
                    out << "</table>";
                    out << "</body>\n</html>";
                    return;
                }
                break; 
            }
        }
    }
}