#include<iostream>

// will choose type of array by the variable used for its size
// there are better uses for this feature
template<auto S>
class MatrixSxS {
public:
    using size_type = decltype(S);
    MatrixSxS();
    auto sizeLength();
    void setPos(const size_type &pos_x, const size_type &pos_y,const size_type &value);
    auto value(const size_type &pos_x, const size_type &pos_y) const { return matrix[pos_x][pos_y]; }
    void print();
private:
    size_type matrix[S][S];
};

template<auto S>
MatrixSxS<S>::MatrixSxS() {
    
}

template<auto S>
auto MatrixSxS<S>::sizeLength() {
    return S;
}

template<auto S>
void MatrixSxS<S>::setPos(const size_type &pos_x, const size_type &pos_y, const size_type &value) {
    matrix[pos_x][pos_y] = value;
}

template<auto S>
void MatrixSxS<S>::print() {
    for(size_type i = 0; i < S; ++i) {
        for(size_type z = 0; z < S; ++z) {
            std::cout << "x: " << i << " y: " << z << " " << matrix[i][z] << "\n";
        }
    }
}

int main() {
    MatrixSxS<8> int_values;
    MatrixSxS<16u> uint_values;
    for(int i = 0; i < 8; ++i) {
        for(int z = 0; z < 8; ++z) {
            int_values.setPos(i, z, (i*z));
        }
    }
    int_values.print();
    for(unsigned int ix = 0; ix < 16; ++ix) {
        for(unsigned int zx = 0; zx < 16; ++zx) {
        	uint_values.setPos(ix, zx, (ix*zx));
        }
    }
    uint_values.print();
    return 0;
}
