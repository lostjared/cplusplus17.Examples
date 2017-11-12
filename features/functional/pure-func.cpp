/*
 The function always evaluates the same result value given the same argument value(s).
 The function result value cannot depend on any hidden information or state that may change
 while program execution proceeds or between different executions of the program, nor can
 it depend on any external input from I/O devices (usually—see below).
 Evaluation of the result does not cause any semantically observable side effect
 or output, such as mutation of mutable objects or output to I/O devices (usually—see below).
*/

#include<iostream>
#include<string>

std::string value="Jared B";

// pure function
// evaluates the same result given the same argument values
std::string function1(std::string &n) {
    return n+"runi";
}

// impure function
// any function that uses a non local variable
std::string function2() {
    return value+"runi";
}

int main() {
    // trying out the code
    std::string name = function1(value);
    std::cout << "pure function: " << name << "\n";
    name = function1(value);
    std::cout << "pure function (again): " << name << "\n";
    name = function2();
    std::cout << "impure function: " << name << "\n";
    value="B";
    name = function2();
    std::cout << "impure function after modifying non-local variable: " << name << "\n";
    return 0;
}
