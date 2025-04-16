#include "ptr.hpp"
#include "int.hpp"

using namespace stds;

struct t {
	int c;
	t() = default;
	t(int a, int b) : c(a + b) {}
};

int main() {
	try {
		int32 n = i32_cast(100ll);
	}
	catch (const code& c) {
	}

	return 0;
}