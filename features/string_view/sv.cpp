#include<iostream>
#include<string>
#include<string_view>

void print_hello(std::string_view sv) {
	std::cout << "Hello: " << sv << "\n";
}

int main() {
	print_hello("Jared");
	print_hello("Person");
	std::string value{" test 1 2 3 "};
	print_hello(value);
	std::string_view sv{value};
	const void *ptr = sv.data();
	int sz = sv.size();
	std::cout << "sv: size:  " << sz << "\n";	
	return 0;
}
