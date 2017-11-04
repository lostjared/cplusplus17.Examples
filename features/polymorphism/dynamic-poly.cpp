#include<iostream>
#include<string>

class Life {
public:
    Life(std::string n) : name(n) {
    }
    virtual ~Life() {
        std::cout << "Life: " << name << " restarts..\n";
    }
    virtual void birth() = 0;
    virtual void death() = 0;
    virtual void say(std::string s) = 0;
    
    std::string getName() const { return name; }
private:
    std::string name;
    
};

class Ape : public Life {
public:
    Ape(std::string n) : Life(n) {
        birth();
    }
    ~Ape() override {
        death();
    }
    void birth() override {
        std::cout << "Ape was born...\n";
    }
    
    void death() override {
        std::cout << "Ape died...\n";
    }
    
    void say(std::string s) override {
        std::cout << "Ape says: " << s << "\n";
    }
};

class Human : public Life {
public:
    Human(std::string n) : Life(n) {
        birth();
    }
    ~Human() override {
        death();
    }
    void birth() override {
        std::cout << "Human was born...\n";
    }
    
    void death() override {
        std::cout << "Human died...\n";
    }
    
    void say(std::string s) override {
        std::cout << "Human says: " << s << "\n";
    }
};

class Alien : public Life {
public:
    Alien(std::string n) : Life(n) {
        birth();
    }
    ~Alien() override {
        death();
    }
    void birth() override {
        std::cout << "Alien was born...\n";
    }
    void death() override {
        std::cout << "Alien died...\n";
    }
    void say(std::string s) override {
        std::cout << "Alien says: " << s << "\n";
    }
};

void SayHello(Life *life) {
    life->say("Hello World!");
}

bool Compare(Life *life1, Life *life2) {
    if(life1->getName() == life2->getName()) return true;
    return false;
}

int main() {
    Human jared("jared");
    Alien grey("grey");
    Ape ceaser("ceaser");
    SayHello(&jared);
    SayHello(&grey);
    SayHello(&ceaser);
    if(Compare(&jared, &ceaser) == true) {
        std::cout << "Comparision true...\n";
    } else {
        std::cout << "Comparision false...\n";
    }
    return 0;
}

