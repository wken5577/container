#include "vector.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>
#include <stack>

int main()
{	
	ft::stack<int> st;
	st.push(1);
	st.push(2);

	ft::stack<int> st2;
	st2.push(1);
	st2.push(2);
	st2.push(3);


	std::stack<int> r_st;
	r_st.push(1);
	r_st.push(2);

	std::stack<int> r_st2;
	r_st2.push(1);
	r_st2.push(2);
	r_st2.push(3);

	bool result = st == st2;
	bool result2 = r_st == r_st2;

	std::cout << result << std::endl;
	std::cout << result2 << std::endl;

	std::cout << st.size() << "\n";
	std::cout << r_st.size() << "\n";
	std::cout << st2.size() << "\n";
	std::cout << r_st2.size() << "\n";
	
	std::cout << st.top() << "\n";
	std::cout << r_st.top() << "\n";
	std::cout << st2.top() << "\n";
	std::cout << r_st2.top() << "\n";

	return 0;
}