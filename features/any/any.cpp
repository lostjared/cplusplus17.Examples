// Cannot compile this myself as the version of the Standard Library it not up to date
// will revisit this when I do.

#include<iostream>
#include<any>

int main() {
    std::any value = 10;
    std::cout << std::any_cast<int>(value) << "\n";
    value = std::string("1 2 3");
    std::cout << std::any_cast<std::string>(value) << "\n";
    return 0;
}
