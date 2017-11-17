
/*

- Jared


*/

#include<iostream>
#include<string>
#include<fstream>

void swapTabSpace(std::istream &in, std::ostream &out, int tabs=4);
void swapSpaceTab(std::istream &in, std::ostream &out, int spaces=4);

int main(int argc, char **argv) {
    if(argc != 3) {
        std::cerr << "must enter number of spaces as argument\n" << argv[0] << " num";
    }
    int num = atoi(argv[2]);
    if(num > 0) {
        if(argv[1][0] == 't')
    		swapTabSpace(std::cin, std::cout, num);
        else
            swapSpaceTab(std::cin, std::cout, num);
    } else {
        std::cerr << "invalid number of spaces..\n";
    }
    return 0;
}

void swapTabSpace(std::istream &in, std::ostream &out, int tabs) {
    std::string t;
    for(int i = 0; i < tabs; i++) {
        t += " ";
    }
    while(!in.eof()) {
        char c = in.get();
        if(in) {
            if(c == '\t') {
                out << t;
            } else {
                out << c;
            }
        }
    }
}

void swapSpaceTab(std::istream &in, std::ostream &out, int spaces) {
    while(!in.eof()) {
        char c = in.get();
        if(in) {
            if(c == ' ') {
                std::string buf;
                buf += c;
                do {
                    c = in.get();
                    if(in && c == ' ') {
                        buf += c;
                    }
                } while(c == ' ');
                if(buf.length() == spaces) {
                    	out << "\t" << c;
                } else {
                    out << buf << c;
                }
            } else {
                out << c;
            }
        }
    }
}

