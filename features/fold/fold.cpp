#include<iostream>

template<typename... Args>
auto Add(Args&&... args) {
    return (args + ...);
}

int main() {
    
    int sum=Add(5,5,25);
    std::cout << "Sum is: " << sum << "\n";
    
    std::string value;
    value=Add(std::string("value 1"), " + value 2 is this");

    std::cout << value << "\n";
    
    return 0;
    
}
