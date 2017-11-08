/*
 Inheritance and
 Reference Counting..
*/
#include<iostream>
#include<string>
#include<type_traits>

// will be able to tell us whether or not a type has a default constructor
template<typename T>
class HasDefaultConstructor {
private:
    template<typename T1, typename = decltype(T1())>
    static std::true_type test(void*);
    
    template<typename>
    static std::false_type test(...);
public:
    static constexpr bool value = std::is_same<decltype(test<T>(nullptr)), std::true_type>::value;
};

template<typename M, typename B>
class Index : public B {
public:
    static_assert(HasDefaultConstructor<M>::value == true, "No default constructor");
    Index() {
        //member = M();
        ++member;
        printNumber();
    }
    
    ~Index() {
        --member;
        printNumber();
    }
    
    void printNumber() {
        std::cout << member << " object(s).\n";
        if(member == 0) {
            std::cout << " at zero delete resources...\n";
        }
    }
    
private:
    inline static M member = M();
};

class Object {
public:
    void say(std::string hello) {
        std::cout << "says: " << hello << "\n";
    }
};

class Test {
public:
    Test() = delete;
    Test(int x) {}
};

using MemberCount = Index<int, Object>;

int main() {
    // Below will fail if uncommented.
   //  Index<Test, Object> fails;
    MemberCount one;
    one.say("Hey ... ");
    for(unsigned int i = 0; i < 3; ++i) {
        MemberCount temp;
        for(unsigned int z = 0; z < 3; ++z) {
            MemberCount temp_i;
        }
    }
    return 0;
}
