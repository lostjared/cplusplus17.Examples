
#include<iostream>
#include<string>

int count_zeros(const std::string &text) {
    int count = 0;
    for(auto &i : text) {
        if(i == '0') ++count;
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
    std::cout << "number of zeros: " << count_zeros(temp) << "\n";
    std::cout << count_zeros("1000") << " zeros in 1000\n";
    
    return 0;
}
