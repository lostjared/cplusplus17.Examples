#include"per.hpp"
#include<ctime>
#include<cstdlib>
#include<vector>

struct Type {
    Type() : x{0}, y{0}, z{0}, value{0.0f} {}
    Type(int xx, int yy, int zz, float v) : x{xx}, y{yy}, z{zz}, value{v} {}
    int x,y,z;
    float value;
};

class UserTypeData {
public:
    UserTypeData() = default;
    
    static void write(std::fstream &file, const Type &type) {
        if(file.is_open())
            file.write(reinterpret_cast<const char*>(&type), sizeof(type));
    }
    
    static void read(std::fstream &file, Type &type) {
        if(file.is_open())
            file.read(reinterpret_cast<char*>(&type), sizeof(type));
    }
};

int main(int argc, char **argv) {
    per::Per<int, per::Data<int>> p("test.dat", 0);
    p.data()++;
    std::cout << "program ran: " << p.data() << "\n";
    
    per::Per<std::vector<int>, per::ContainerData<std::vector<int>, int>> vp("vec.dat");
    srand(static_cast<int>(time(0)));
    vp.data().push_back(rand()%255);

    for(auto it = vp.data().begin(); it != vp.data().end(); ++it)
        std::cout << *it << "\n";
    
    per::Per<std::string, per::StringData> sp("string.dat", "Hello World ");
    sp.data() += "0";
    
    std::cout << sp.data() << "\n";
    
    per::Per<std::vector<std::string>, per::StringContainerData<std::vector<std::string>>> svp("svec.dat");
    
    svp.data().push_back(sp.data());
    
    for(auto it = svp.data().begin(); it != svp.data().end(); ++it)
        std::cout << "string data: " << *it << "\n";
    
    per::Per<Type, UserTypeData> utype("utype.txt", Type(0,0,0,1.0));
    utype.data().x++;
    std::cout << "x val: " << utype.data().x << "\n";
    
    return 0;
}
