#include "vector.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include "red_black_tree.hpp"
#include "pair.hpp"
#include <map>

int main()
{	
	// ft::RBTree<int, std::string> tree;
	// tree.insertNode(ft::make_pair(35, "35"));
	// tree.insertNode(ft::make_pair(20, "20"));
	// tree.insertNode(ft::make_pair(10, "10"));
	// tree.insertNode(ft::make_pair(30, "30"));
	// tree.insertNode(ft::make_pair(50, "40"));
	// tree.insertNode(ft::make_pair(40, "40"));
	// tree.insertNode(ft::make_pair(80, "60"));
	// tree.insertNode(ft::make_pair(5, "70"));
	// tree.insertNode(ft::make_pair(15, "80"));
	// tree.insertNode(ft::make_pair(25, "90"));
	// tree.insertNode(ft::make_pair(33, "100"));
	// tree.insertNode(ft::make_pair(37, "110"));
	// tree.insertNode(ft::make_pair(45, "120"));
	// tree.insertNode(ft::make_pair(2, "130"));
	// tree.insertNode(ft::make_pair(27, "22"));

	// tree.deleteNode(15);
	// tree.deleteNode(33);
	// tree.deleteNode(37);
	// tree.deleteNode(35);
	// tree.deleteNode(40);
	// tree.deleteNode(50);
	// tree.deleteNode(80);
	// tree.deleteNode(27);
	// tree.printRBTree(tree.getTreeHead());

	// std::allocator<ft::pair<const int, int> > alloc;

	// ft::pair<const int, int> *pa = alloc.allocate(1, pa);

	std::map<int, float> num_map;
  	num_map.insert(std::make_pair(1, 2.3));
	num_map.insert(std::make_pair(3, 2.3));
	num_map.insert(std::make_pair(2, 2.3));

	std::map<int, float>::iterator it = num_map.begin();
	std::map<int, float>::iterator itend = num_map.end();

	while (it != itend)
	{
		std::cout << (*it).first << "   " << it->second << "\n";
		it++;
	}

	return 0;
}
