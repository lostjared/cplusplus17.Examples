/*
 C++17 Example
 tested with Clang-3.9
*/

#include<iostream>
#include<vector>
#include<algorithm>

// function using if statement with new syntatic sugar
template<typename T>
bool VecRemove(std::vector<T> &vec, const T &search) {
    if(auto pos(std::find(vec.begin(), vec.end(), search)); pos != vec.end()) {
        vec.erase(pos);
        return true;
    }
    return false;
}

int main(int argc, char **argv) {
    std::vector<std::string> v {"Jared", "Monkey", "Cow", "Turkey", "Pumpkin" };
    // cool initilization for if statement
    if(int sz(v.size()); sz > 3) {
        std::cout << "Yeah it works value is: " << sz << "\n";
    }
    // remove string Monkey from Vector
    if(VecRemove<std::string>(v, "Monkey")) {
        std::cout << "Removed string\n";
    }
    std::cout << "Enter character: \n";
    // cool initalization statement for swtich
    switch(auto c(getchar()); c) {
        case 'q':
            exit(0);
            break;
        case 'b':
            std::cout << "You pressed b.\n";
            break;
        default:
            std::cout << "You did not press b.\n";
    }
    
    return 0;
}
