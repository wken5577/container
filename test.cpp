#include "vector.hpp"
#include <iostream>
#include <vector>
#include <stack>

int main()
{	
	ft::vector<int> v1;
	v1.push_back(0);
	v1.push_back(1);

	ft::vector<int> v2 = v1;
	v2.push_back(3);

	for(int i = 0; i < v1.size(); i++)
	{
		std::cout << v1[i] << " ";
	}
	std::cout << "\n";

	for(int i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << " ";
	}
	
	std::stack<int> s1;
}