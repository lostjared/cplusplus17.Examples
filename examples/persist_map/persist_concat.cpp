#include"permap.hpp"
#include<iostream>


int main() {
    persist::PersistMap<int> program_ran("ran.dat", persist::GenericRead<int>, persist::GenericWrite<int>);
    program_ran["run_times"]++;
    std::cout << "Program Ran: " << program_ran["run_times"] << "\n";
    persist::PersistMap<int> program_this("ran_this.dat", persist::GenericRead<int>, persist::GenericWrite<int>);
    program_this << program_ran;
    std::cout << "Enter some text: ";
    std::string text;
    std::cin >> text;
    program_ran[text] = rand()%0xFFFFFFFF;
    std::cout << "Concat PersistMap1, PersistMap2: \n";
    for(auto i = program_ran->begin(); i != program_ran->end(); ++i) {
        std::cout << "Key: " << i->first << " " << " Value: " << i->second << "\n";
    }
    return 0;
}
