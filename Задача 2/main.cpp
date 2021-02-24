#include <iostream>
#include <cmath>

unsigned int hash(double d)
{
	auto h = 0U;
	h = fmod(d, 17) * pow(d, 3);
	return fmod(h, 128);
}

int main(int argc, char ** argv)
{
	std::cout << hash(52.489) << std::endl;
	std::cout << hash(92.106) << std::endl;
	std::cout << hash(1.0098) << std::endl;
	std::cout << hash(52.33) << std::endl;

	return 0;
}
