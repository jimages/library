#include "pow.h"
#include <iostream>

int main() {
	long long a;
	double b, base;
	std::cout << "a> " << std::flush;
	std::cin >> a;
	std::cout << "b> " << std::flush;
	std::cin >> b;
	std::cout << "base> " << std::flush;
	std::cin >> base;
	std::cout << "getPower(int ,int) = " << getPower(a, base) << std::endl;
	std::cout << "getPower(double, int) = " << getPower(b, base) << std::endl;
	return 0;
}
