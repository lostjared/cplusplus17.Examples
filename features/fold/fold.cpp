#include<iostream>

template<typename... Args>
auto Add(Args&&... args) {
    return (args + ...);
}


template<typename... Args>
void printValues(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

int main() {
    
    int sum=Add(5,5,25);
    std::cout << "Sum is: " << sum << "\n";
    
    std::string value;
    value=Add(std::string("value 1"), " + value 2 is this");

    std::cout << value << "\n";
    
    printValues(1, 2, 3, 4);
    printValues("one ", "two ", "three ");
    
    return 0;
    
}
