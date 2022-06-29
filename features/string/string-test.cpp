// convert integer to string
#include<iostream>
#include<string>

int main() {
    std::cout << "Value: ";
    int x = 0;
    std::cin >> x;
    std::string temp;
    temp = std::to_string(x);
    std::cout << "value is: " + temp << "\n";
    return 0;
}
