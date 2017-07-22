#include<iostream>

int main() {
	double value1 = 0xFF.2p3; // scaled by exponent
	double value2 = 0x1E.4p7; // scaled by exponent
	std::cout << value1 << " + " << value2 << " = " << (value1+value2) << "\n";
	double value3 = 0x1.2p3; // 9
	std::cout << value3 << " + " << value3 << " = " << (value3+value3) << "\n";
	return 0;
}
