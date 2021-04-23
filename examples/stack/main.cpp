#include"stack.hpp"

int main(int argc, char **argv) {
    try {
        Stack<int> stack1(100);
        stack1.push(100);
        stack1.push(200);
        stack1.printItems();
        int val = stack1.pop();
        std::cout << "off top: " << val << "\n";
        val = stack1.pop();
        std::cout << "off top: " << val << "\n";
        stack1.printItems();
    } catch (ErrorUnder &eu) {
        std::cout << "underflow\n";
    } catch (ErrorOver &eo) {
        std::cout << "overflow\n";
    } catch(...) {
        std::cout << "...\n";
    }
    return 0;
}
