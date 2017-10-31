/*
 	Some ways you can use Lambdas
*/

#include<iostream>
#include<vector>
#include<string>

template<typename Iter, typename F>
void iterate(Iter start, Iter stop, F func) {
    while(start != stop){
        func(*start);
        start++;
    }
}

int main() {
    std::vector<int> value { 100, 200, 300, 400 };
    iterate(value.begin(), value.end(),[](int x) {
        std::cout << "value: " << x << "\n";
    });
    iterate(value.begin(), value.end(), [](auto x) {
        std::cout << "value is: " << x << "\n";
    });
    auto f = [](auto x, auto y) {
        return (x+y);
    };
    std::cout << "Value + is: " << f(100, 200) << "\n";
    
    auto ConcatAddNewLine = [](std::string x, std::string y) -> std::string {
        return x+y+"\n";
    };
    std::string string1 = "Hello, ";
    std::string string2 = " World!";
    std::cout <<  ConcatAddNewLine(string1, string2);
    std::cout << "Using auto: " << f(string1, string2) << "\n";
    return 0;
}
