
#include<iostream>
#include<string>

int count_zeros(const std::string &text) {
    int count = 0;
    for(auto &i : text) {
        if(i == '0') ++count;
    }
    return count;
}

template<typename Iter>
int count_chars(char c, Iter start, Iter stop) {
    int count = 0;
    for(Iter i = start; i != stop; ++i) {
        if(*i == c) ++count;
    }
    return count;
}

int main() {
    // convert integer to string
    std::cout << "Value: ";
    int x = 0;
    std::cin >> x;
    std::string temp;
    temp = std::to_string(x);
    std::cout << "value is: " + temp << "\n";
    std::cout << count_chars('0', temp.begin(), temp.end()) << " zeros in string with template.\n";
    
    std::cout << "number of zeros: " << count_zeros(temp) << "\n";
    std::cout << count_zeros("1000") << " zeros in 1000\n";
    
    return 0;
}
