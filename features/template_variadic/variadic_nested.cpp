/*

 Nested Variadic Template example

*/

#include<iostream>

template<typename... Args>
class Outer {
public:
    template<Args... args>
    class Inner {
    public:
        template<typename T>
        void TestOutput(T type) {
            std::cout << "Argument: " << type << "\n";
        }
        template<typename T, typename... Type>
        void TestOutput(T val, Type... type) {
            TestOutput(val);
            TestOutput(type...);
        }
        void PrintValues(Args... argx) {
            std::cout << sizeof...(argx) << " arguments.\n";
            TestOutput(args...);
            TestOutput(argx...);
        }
    };
};

int main() {
    Outer<int, char, int>::Inner<10, 'a', 25> c;
    c.PrintValues(12, 'b', 26);
    return 0;
}
