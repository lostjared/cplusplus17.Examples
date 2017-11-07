/*
 Inheritance and
 Reference Counting..
*/
#include<iostream>
#include<string>


template<typename M, typename B>
class Index : public B {
public:
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

using MemberCount = Index<int, Object>;

int main() {
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
