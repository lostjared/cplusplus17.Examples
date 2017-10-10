
// for some reason on clang++-5.0 library invoke is declared __invoke
// comment this out if using a new/other compiler with correct name
#define invoke __invoke

// invoke will allow you to use different types to be called including, function, function pointer
// functor or member function pointer

#include<iostream>
#include<functional>
#include<utility>
#include<vector>

template<typename It, typename Call, typename... Args>
void my_foreach(It start, It stop, Call call, Args... args) {
    while(start != stop) {
        std::invoke(call, args..., *start);
        start++;
    }
}

class ProcOutput {
public:
    void operator()(int x) {
        std::cout << "Value +1 is: " << (x+1) << "\n";
    }
    
    void memfunc(int x) {
        std::cout << "Value -1 is: " << (x-1) << "\n";
    }
};

int main() {
    std::vector<int> values {0,2,8,12,64,128,69,48,180};
    my_foreach(values.begin(), values.end(), [](int value) {
        std::cout << "Value is: " << value << "\n";
    });
    my_foreach(values.begin(), values.end(), ProcOutput());
    ProcOutput proc;
    my_foreach(values.begin(), values.end(), &ProcOutput::memfunc, proc);
    return 0;
}
