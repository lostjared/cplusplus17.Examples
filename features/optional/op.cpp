#include<iostream>
#include<optional>
#include<string>

std::optional<int> getCmd() {
    std::optional<int> op;
    std::cout << "enter command: (quit/print) ";
    std::string s;
    std::cin >> s;
    if(s == "quit")
        op = 1;
    else if(s == "print")
        op = 2;
   
    return op;
}

int main() {

    auto i = getCmd();
    if(i) {
        std::cout << "Command is: " << *i << "\n";
        switch(*i) {
            case 1:
                std::cout << "Goodbye!.\n";
                exit(0);
                break;
            case 2:
                std::cout << "Print...\n";
                break;
        }
    } else {
        std::cout << "Unknown command: \n";
    }
    
    
    
    return 0;
}
