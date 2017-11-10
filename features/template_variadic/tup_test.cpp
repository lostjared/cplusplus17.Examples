#include<iostream>
#include<tuple>

// Store pack in a tuple
template<typename... Args>
class Test {
public:
    std::tuple<Args...> val;
    Test(Args... args) : val(args...) {}
    
    template<int V>
    void printElement() {
        std::cout << "Index at: " << V << " value = " << std::get<V>(val) << "\n";
    }
};

int main() {
    Test<int, char, long> v(0, 'a', 10);
    v.printElement<0>();
    v.printElement<1>();
    v.printElement<2>();
    return 0;
}
