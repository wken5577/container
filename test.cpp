#include "vector.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include "red_black_tree.hpp"
#include "pair.hpp"
#include <map>
#include "map.hpp"

int main()
{	

	// ft::map< int, float> num_map;
  	// num_map.insert(ft::make_pair(1, 2.3));
	// num_map.insert(ft::make_pair(1, 20.2));
	// num_map.insert(ft::make_pair(3, 2.3));
	// num_map.insert(ft::make_pair(2, 2.3));
	// num_map.insert(ft::make_pair(5, 2.3));
	// num_map.insert(ft::make_pair(7, 2.3));

	// std::cout << num_map.at(1) << "\n";
	// num_map.clear();
	// std::cout << num_map.size() << "\n";
	// num_map.at(1);


	// ft::map< int, float>::reverse_iterator it1 = num_map.rbegin();
	// ft::map< int, float>::reverse_iterator it2 = num_map.rend();

	// it2--;
	// std::cout << "it1 = " << it1->first << " " << it1->second << "\n";
	// std::cout << "it2 = " << it2->first << " " << it2->second << "\n";
	// std::cout << (it2 <= it1) << "\n";




	// ft::vector<int> v1;
	// v1.push_back(1);
	// v1.push_back(2);

	// ft::vector<int>::reverse_iterator v_it1 = v1.rbegin();
	// ft::vector<int>::reverse_iterator v_it2 = v1.rend();

	// v_it2--;
	// std::cout << "v_it1 = " << *v_it1 << "\n";
	// std::cout << "v_it2 = " << *v_it2 << "\n";
	// std::cout << (v_it1 <= v_it2) << "\n";


	ft::map<int, float> map;
	map.insert(ft::make_pair<int, float>(1, 5.1));
	map.insert(ft::make_pair<int, float>(2, 1.4));
	map.insert(ft::make_pair<int, float>(3, 2.5));
	map.insert(ft::make_pair<int, float>(4, 2.1));

	auto p = map.equal_range(3);
	for (auto& q = p.first; q != p.second; ++q) {
            std::cout << "m[" << q->first << "] = " << q->second << '\n';
    }
	return 0;
}
