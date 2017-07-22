
// C++17 Example

#include"nested_namespace.hpp"

// namespace sub/namespaces can be declared in single statement
// with new Nested namespace definition
namespace X::Y::Z {
	int x = 0;
}

// output value 0 for x
int main(int argc, char **argv) {
	std::cout << "Value X: " << X::Y::Z::x << "\n";
	return 0;
}
