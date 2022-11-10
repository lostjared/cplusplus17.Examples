// visitor with std::variant
#include<iostream>
#include<string>
#include<variant>
#include<vector>

class ObjectType1 {
public:
    ObjectType1() = default;
    int x = 1;
};

class ObjectType2 {
public:
    ObjectType2() = default;
    double x = 1.0;
};

class PrintTypes {
public:
    void operator()(const ObjectType1 &t) const {
        std::cout << "Type1: " << t.x << "\n";
    }
    void operator()(const ObjectType2 &t) const {
        std::cout << "Type2: " << t.x << "\n";
    }
};

using obj_t = std::variant<ObjectType1,ObjectType2>;
using vobj_t = std::vector<obj_t>;

void printAllTypes(const vobj_t &all) {
    for(auto &i : all) {
        std::visit(PrintTypes{}, i);
    }
}

int main(int argc, char **argv) {
    vobj_t obj_collection;
    obj_collection.push_back(ObjectType2{});
    obj_collection.push_back(ObjectType1{});
    printAllTypes(obj_collection);
    return 0;
}

