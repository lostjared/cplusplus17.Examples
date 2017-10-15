#include<iostream>
#include<vector>

int main() {
    enum class Option { OP_1, OP_2, OP_3 };
    Option o = Option::OP_1;
    for(unsigned int i = 0; i < 1000; ++i) {
        switch(Option q = o; q) {
            case Option::OP_1:
                o = Option::OP_2;
                std::cout << "Option 1\n";
                break;
            case Option::OP_2:
                o = Option::OP_3;
                std::cout << "Option 2\n";
                break;
            case Option::OP_3:
                o = Option::OP_1;
                std::cout << "Option 3\n";
                break;
        }
    }
    return 0;
}
