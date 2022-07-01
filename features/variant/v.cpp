#include<variant>
#include<iostream>
#include<string>
#include<vector>

using VType = std::variant<int, std::string>;

int main() {
    std::vector<VType> v{10, "Hello", 25};
    for(auto &i : v) {
        std::visit([](const auto &obj) {
            std::cout << obj << "\n";
        }, i);
    }
    
    VType v1;
    
    v1 = 42;
    
    std::cout << v1.index() << ": " << std::get<int>(v1) << "\n";

    v1 = "test";
    
    std::cout << v1.index() << ": " << std::get<std::string>(v1) << "\n";

    
    return 0;
}
