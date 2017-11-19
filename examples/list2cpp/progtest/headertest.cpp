#include"header.hpp"
#include"outputbytes.hpp"
#include<iostream>
#include<iomanip>

int main() {
    	for(unsigned long i = 0; i < varname_size; ++i) {
        	std::cout << varname_arr[i] << "\n";
    	}

	std::cout << bytes_arr << "\n";

	for(unsigned long i = 0; i < bytes_size; ++i) {
		std::cout << std::dec << "[" << i << "] = " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<unsigned int>(bytes_arr[i]) << "\n";
	}
	return 0;
}
