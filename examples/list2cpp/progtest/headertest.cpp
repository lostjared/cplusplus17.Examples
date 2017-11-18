#include"header.hpp"
#include"outputbytes.hpp"
#include<iostream>

int main() {
    	for(unsigned long i = 0; i < varname_size; ++i) {
        	std::cout << varname_arr[i] << "\n";
    	}

	std::cout << bytes_arr << "\n";
	return 0;
}
