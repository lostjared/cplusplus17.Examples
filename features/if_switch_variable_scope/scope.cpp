#include<iostream>
#include<vector>

int main(int argc, char **argv) {
    std::vector<std::string> v {"Jared", "Monkey", "Cow", "Turkey", "Pumpkin" };
    // cool initilization for if statement
    if(int sz(v.size()); sz > 3) {
        std::cout << "Yeah it works value is: " << sz << "\n";
    }
    
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
