#include <cstddef>
#include <iostream>
#include "reverse_iterator.hpp"
#include <vector>
#include <limits>

int main()
{
	std::vector<long> v1;
	std::cout << v1.max_size() << std::endl;
	std::cout << (std::size_t)(std::numeric_limits<long>::max() - 1) << std::endl;
}
