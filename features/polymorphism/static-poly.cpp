#include<iostream>
#include<string>
#include<vector>

class Ape {
public:
    Ape(std::string n) : name(n) {
        birth();
    }
    ~Ape() {
        death();
    }
    void birth() {
        std::cout << "Ape: Born..\n";
    }
    void death() {
        std::cout << "Ape: Death..\n";
    }
    void say(std::string s) {
        std::cout << "Ape says: " << s << "\n";
    }
    
    std::string getName() const { return name; }
    
private:
    std::string name;
};

class Human {
public:
    Human(std::string n) : name(n) {
        birth();
    }
    ~Human() {
        death();
    }
    void birth() {
        std::cout << "Human was born..\n";
    }
    
    void death() {
        std::cout << "Human died..\n";
    }
    void say(std::string s) {
        std::cout << "Human says: " << s << "\n";
    }
    std::string getName() const { return name; }
    
private:
    std::string name;

};

class Alien {
public:
    Alien(std::string n) : name(n) {
        birth();
    }
    ~Alien() {
        death();
    }
    void birth() {
        std::cout << "Alien was born..\n";
    }
    void death() {
        std::cout << "Alien died..\n";
    }
    
    void say(std::string s) {
        std::cout << "Alien says: " << s << "\n";
    }
    std::string getName() const { return name; }
    
private:
    std::string name;

};


template<typename T>
void SayHello(T &type) {
    type.say("Hello World!");
}

template<typename T1, typename T2>
bool CompareName(T1 &type1, T2 &type2) {
    if(type1.getName() == type2.getName())
        return true;
    
   return false;
}


int main() {

    Human jared("jared");
    Alien grey("grey");
    Ape ceaser("ceaser");
    
    SayHello(jared);
    SayHello(ceaser);
    SayHello(grey);

    if(CompareName(jared,ceaser)==true) {
        std::cout << "Have same name..\n";
    } else {
        std::cout << "Do not have the same name..\n";
    }
    return 0;
}
