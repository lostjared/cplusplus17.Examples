#include"rw.hpp"
#include<iostream>

int main() {
    System::out.println("Hello, ", "World", "!");
    System::out.print("Enter value: ");
    int valueX = 0, valueY = 0;
    System::in.read(valueX);
    System::in.read(valueY);
    System::out.println(valueX, "*", valueY, "=", (valueX*valueY));
    return 0;
}
