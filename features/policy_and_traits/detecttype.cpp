#include<iostream>
#include<string>
#include<type_traits>

enum VAR_TYPE { TYPE_NOTDEFAULT, TYPE_LDOUBLE, TYPE_DOUBLE,
    TYPE_FLOAT, TYPE_ULLONG, TYPE_SLLONG, TYPE_ULONG, TYPE_SLONG,
    TYPE_UINT, TYPE_SINT, TYPE_USHORT, TYPE_SSHORT, TYPE_UCHAR, TYPE_SCHAR,
  TYPE_WCHAR, TYPE_CHAR16, TYPE_CHAR32, TYPE_BOOL, TYPE_VOID
};

std::ostream &operator<<(std::ostream &out, VAR_TYPE type);

template<typename T>
class DefaultType {
public:
    static constexpr VAR_TYPE type = TYPE_NOTDEFAULT;
};

#define BUILT_IN(T,TYPE) \
template<> class DefaultType<T>  { \
public: \
static constexpr VAR_TYPE type = TYPE; \
};


BUILT_IN(long double, TYPE_LDOUBLE)
BUILT_IN(double, TYPE_DOUBLE)
BUILT_IN(float, TYPE_FLOAT)
BUILT_IN(unsigned long long, TYPE_ULLONG)
BUILT_IN(signed long long, TYPE_SLLONG)
BUILT_IN(unsigned long, TYPE_ULONG)
BUILT_IN(signed long, TYPE_SLONG)
BUILT_IN(unsigned int, TYPE_UINT)
BUILT_IN(signed int, TYPE_SINT)
BUILT_IN(unsigned short, TYPE_USHORT)
BUILT_IN(signed short, TYPE_SSHORT)
BUILT_IN(unsigned char, TYPE_UCHAR)
BUILT_IN(char, TYPE_SCHAR)
BUILT_IN(wchar_t, TYPE_WCHAR)
BUILT_IN(char16_t, TYPE_CHAR16)
BUILT_IN(char32_t, TYPE_CHAR32)
BUILT_IN(bool, TYPE_BOOL)
BUILT_IN(void, TYPE_VOID)


template<typename T>
void EchoType(const T &type) {
    std::cout << "Parameter is of type: " << DefaultType<T>::type << "\n";
}

template<typename T, typename... Args>
void EchoType(const T &type, Args... args) {
    EchoType(type);
    EchoType(args...);
}

int main() {
    EchoType(100, 100.4, 'c', 100u, 150.0f, std::string("HEY"));
    return 0;
}

std::ostream &operator<<(std::ostream &out, VAR_TYPE type) {
    switch(type) {
        case TYPE_NOTDEFAULT:
            out << "Not Default";
            break;
        case TYPE_LDOUBLE:
            out << "long double";
            break;
        case TYPE_DOUBLE:
            out << "double";
            break;
        case TYPE_FLOAT:
            out << "float";
            break;
        case TYPE_ULLONG:
            out << "unsigned long long";
            break;
        case TYPE_SLLONG:
            out << "signed long long";
            break;
        case TYPE_ULONG:
            out << "unsigned long";
            break;
        case TYPE_SLONG:
            out << "signed long";
            break;
        case TYPE_UINT:
            out << "unsigned int";
            break;
        case TYPE_SINT:
            out << "signed int";
            break;
        case TYPE_USHORT:
            out << "unsigned short";
            break;
        case TYPE_SSHORT:
            out << "signed short";
            break;
        case TYPE_UCHAR:
            out << "unsigned char";
            break;
        case TYPE_SCHAR:
            out << "signed char";
            break;
        case TYPE_WCHAR:
            out << "whcar_t";
            break;
        case TYPE_CHAR16:
            out << "char16_t";
            break;
        case TYPE_CHAR32:
            out << "char32_t";
            break;
        case TYPE_BOOL:
            out << "bool";
            break;
        case TYPE_VOID:
            out << "void";
            break;
        default:
            out << "Unknown type..\n";
            break;
            
    }
    return out;
}

