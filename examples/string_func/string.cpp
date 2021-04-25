// old school functions
#include<iostream>
#include<string>

std::string mid(const std::string &src, size_t start, size_t stop) {
    std::string temp;
    for(size_t i = start; i < stop; ++i) {
        temp += src[i];
    }
    return temp;
}

std::string left(const std::string &src, size_t num) {
    std::string temp;
    for(size_t i = 0; i < num; ++i) {
        temp += src[i];
    }
    return temp;
}

std::string right(const std::string &src, size_t num) {
    std::string temp;
    for(size_t i = num; i < src.length(); ++i) {
        temp += src[i];
    }
    return temp;
}

int main(int argc, char **argv) {
    std::string src="abc 123 efg";
    std::string one, two, three;
    one=mid(src,3,5);
    std::cout << one << "\n";
    two=left(src,3);
    std::cout << two << "\n";
    three=right(src,3);
    std::cout << three << "\n";
    return 0;
}
