#include<iostream>
#include<string>

template<typename T>
class Multi_Dim {
public:
    explicit Multi_Dim(int size_x, int size_y) {
        value = nullptr;
        arr_x = arr_y = 0;
        sizeArray(size_x, size_y);
    }
    
    ~Multi_Dim() {
        eraseArray();
    }
    
    void sizeArray(int size_x, int size_y) {
        if(value != nullptr) {
            eraseArray();
        }
        std::cout << "Sizing array to: [" << size_x << "][" << size_y << "]\n";
        value = new T*[size_x];
        for(int i = 0; i < size_x; ++i) {
            value[i] = new T[size_y];
        }
        arr_x = size_x;
        arr_y = size_y;
    }
    
    void eraseArray() {
        if(value == nullptr) return;
        std::cout << "Cleaning up array...\n";
        for(int i = 0; i < arr_x; ++i) {
            delete [] value[i];
        }
        delete [] value;
        value = nullptr;
    }
    
    T &at(unsigned int x, unsigned int y) {
        return value[x][y];
    }
    
    T &operator()(unsigned int x, unsigned int y) {
        return at(x,y);
    }
    
    int X() const { return arr_x; }
    int Y() const { return arr_y; }
    
private:
    T **value;
    int arr_x, arr_y;
};

int main() {
    Multi_Dim<std::string> values(100, 100);
    for(int x = 0;  x < values.X(); ++x) {
        for(int y = 0; y < values.Y(); ++y) {
            std::string &value = values.at(x,y);
            value = "Test 1 2 3";
        }
    }
    
    for(int x = 0;  x < values.X(); ++x) {
        for(int y = 0; y < values.Y(); ++y) {
            std::string &value = values.at(x,y);
            std::cout << value << "\n";
        }
    }

    return 0;
}
