#include "string.hpp"

using namespace stds;

struct t {
	int c;
	t() = default;
	t(int a, int b) : c(a + b) {}
};

int main() {
	try {
	}
	catch (const code& c) {
		std::cout << "code: " << c.value;
	}

	return 0;
}