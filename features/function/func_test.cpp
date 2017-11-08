/* Some different ways you can use std::function */
#include<iostream>
#include<string>
#include<functional>


void func_test(const std::string &x) {
    std::cout << "say: " << x << "\n";
}

void for_loop(std::string word, int numTimes, std::function<void(std::string)> func) {
    for(int i = 0; i < numTimes; ++i) {
        std::cout << "at index: " << i << " ";
        func(word);
    }
}

int main() {

    std::function<void(std::string)> func1 = func_test;
    func_test("Hello World");
    std::function<void(int)> printNum = [](int x) -> void {
        std::cout << "num value: " << x << "\n";
    };
    printNum(100);
    for_loop("Hey its me", 10, [](std::string n) -> void {
        std::cout << n << "\n";
    });
    
    return 0;
}
