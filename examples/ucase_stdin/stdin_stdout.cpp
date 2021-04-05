#include<iostream>
#include<cctype>
#include<cstdlib>

// uppercase standard input stream
int main(int argc, char **argv) {
    while(!std::cin.eof()) {
        int c = std::cin.get();
        std::cout << static_cast<char>(toupper(c));
    }
	return 0;
}
