#include "vector.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include "red_black_tree.hpp"
#include "pair.hpp"

int main()
{	
	RBTree<int, std::string> tree;
	tree.insertNode(ft::make_pair(35, "35"));
	tree.insertNode(ft::make_pair(20, "20"));
	tree.insertNode(ft::make_pair(10, "10"));
	tree.insertNode(ft::make_pair(30, "30"));
	tree.insertNode(ft::make_pair(50, "40"));
	tree.insertNode(ft::make_pair(40, "40"));
	tree.insertNode(ft::make_pair(80, "60"));
	tree.insertNode(ft::make_pair(5, "70"));
	tree.insertNode(ft::make_pair(15, "80"));
	tree.insertNode(ft::make_pair(25, "90"));
	tree.insertNode(ft::make_pair(33, "100"));
	tree.insertNode(ft::make_pair(37, "110"));
	tree.insertNode(ft::make_pair(45, "120"));
	tree.insertNode(ft::make_pair(2, "130"));
	tree.insertNode(ft::make_pair(27, "22"));

	tree.deleteNode(15);
	tree.deleteNode(33);
	tree.deleteNode(37);
	tree.deleteNode(35);
	tree.deleteNode(40);
	tree.deleteNode(50);
	tree.deleteNode(80);
	tree.deleteNode(27);
	tree.printRBTree(tree.head);
	return 0;
}