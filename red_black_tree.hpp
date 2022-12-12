#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include <iostream>

typedef enum NodeType
{
	NRed = 0,
	NBlack,
} NodeType;

template <typename KEY, typename VAL, typename T=std::pair<KEY, VAL>, class Compare = std::less<KEY> >
class RBTree
{
	class TNode
	{
	public:
		T 				data;
		NodeType 		type;
		TNode 			*parent;
		TNode 			*left;
		TNode 			*right;

	public:
		TNode(T data, NodeType type)
		:data(data), type(type), parent(nullptr), left(nullptr), right(nullptr)
		{}

		friend bool operator<( const TNode& lhs, const TNode& rhs)
		{
			return Compare(lhs.data.first, rhs.data.first);
		}
	};

public:
	TNode 	*head;
	Compare	_comp;

	TNode *makeNewNode(T data, NodeType type)
	{
		return new TNode(data, type);
	}

	void insertNewRedNode(TNode *newNode)
	{
		TNode *tar = head;
		TNode *parent = head->parent;

		while (tar)
		{
			while (tar &&_comp(newNode->data.first, tar->data.first))
			{
				parent = tar;
				tar = tar->left;
			}
			while (tar && _comp(tar->data.first, newNode->data.first))
			{
				parent = tar;
				tar = tar->right;
			}
			if (tar && tar->data.first == newNode->data.first)
			{
				newNode->parent = tar->parent;
				newNode->left = tar->left;
				newNode->right = tar->right;
				if (_comp(newNode->data.first, parent->data.first))
					parent->left = newNode;
				else
					parent->right = newNode;
				delete tar;
				return;
			}
		}
		newNode->parent = parent;
		if (_comp(newNode->data.first, parent->data.first))
			parent->left = newNode;
		else
			parent->right = newNode;
	}

	void searchNode(TNode *head, TNode **tar)
	{
		if (!head)
			return;
		if (head->type == NRed && head->left && head->left->type == NRed)
		{
			*tar = head->left;
			return;
		}
		else if (head->type == NRed && head->right && head->right->type == NRed)
		{
			*tar = head->right;
			return;
		}
		searchNode(head->left, tar);
		searchNode(head->right, tar);
	}

	TNode *isDoubleRed()
	{
		TNode *tar = nullptr;
		searchNode(head, &tar);
		return tar;
	}

	void linkRestructData(TNode  **nodeList)
	{
		nodeList[1]->left = nodeList[0];
		nodeList[0]->parent = nodeList[1];
		if (nodeList[0]->left == nodeList[1] || nodeList[0]->left == nodeList[2])
			nodeList[0]->left = nullptr;
		if (nodeList[0]->right == nodeList[1] || nodeList[0]->right == nodeList[2])
			nodeList[0]->right = nullptr;

		nodeList[1]->right = nodeList[2];
		nodeList[2]->parent = nodeList[1];
		if (nodeList[2]->left == nodeList[1] || nodeList[2]->left == nodeList[0])
			nodeList[2]->left = nullptr;
		if (nodeList[2]->right == nodeList[1] || nodeList[2]->right == nodeList[1])
			nodeList[2]->right = nullptr;

		nodeList[1]->type = NBlack;
		nodeList[1]->left->type = NRed;
		nodeList[1]->right->type = NRed;
	}

	void doRestruct(TNode *dblRedTarget)
	{
		TNode *p = dblRedTarget->parent;
		TNode *g = dblRedTarget->parent->parent;
		TNode *n = dblRedTarget;
		TNode *gp = g->parent;

		TNode  *nodeList[3];

		nodeList[0] = g;
		nodeList[1] = p;
		nodeList[2] = n;

		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 2 - i; j++)
			{
				TNode *tmp;
				if (_comp(nodeList[j + 1]->data.first, nodeList[j]->data.first))
				{
					tmp = nodeList[j + 1];
					nodeList[j + 1] = nodeList[j];
					nodeList[j] = tmp;
				}
			}
		}
		linkRestructData(nodeList);
		nodeList[1]->parent = gp;
		if (nodeList[1] == head)
			head = nodeList[1];
		if (gp && _comp(nodeList[1]->data.first, gp->data.first))
			gp->left = nodeList[1];
		else if (gp && _comp(gp->data.first, nodeList[1]->data.first))
			gp->right = nodeList[1];
	}

	void doRecoloring(TNode *dblRedTarget)
	{
		TNode *p = dblRedTarget->parent;
		TNode *g = dblRedTarget->parent->parent;
		TNode *n = dblRedTarget;
		TNode *u;

		if (g->left == p)
			u = g->right;
		else
			u = g->left;
		p->type = NBlack;
		u->type = NBlack;
		g->type = NRed;
		if (g == head)
		{
			g->type = NBlack;
			head = g;
		}
	}

	void doRestructRecoloring(TNode *dblRedTarget)
	{
		TNode *u;
		TNode *g = dblRedTarget->parent->parent;
		TNode *p = dblRedTarget->parent;
		if (g->left == p)
			u = g->right;
		else
			u = g->left;
		if (u == nullptr || u->type == NBlack)
			doRestruct(dblRedTarget);
		 else
		 	doRecoloring(dblRedTarget);
	}

public:
	RBTree()
	:head(nullptr)
	{}

	void printRBTree(TNode *head)
	{
		if(!head)
			return;
		printRBTree(head->left);
		std::cout << head->data.first << " " <<  head->data.second << " ";
		if (head->type == NBlack)
			std::cout << "Black" << "\n";
		else
			std::cout << "Red" << "\n";
		printRBTree(head->right);
	}

	void insertNode(T data)
	{
		if (!head)
		{
			TNode *newNode = makeNewNode(data, NBlack);
			head = newNode;
			return ;
		}
		TNode *newNode = makeNewNode(data, NRed);
		insertNewRedNode(newNode);
		TNode *dblRedTarget = isDoubleRed();
		while (dblRedTarget)
		{
		 	doRestructRecoloring(dblRedTarget);
			dblRedTarget = isDoubleRed();
		}
	}

	void deleteNode(T data)
	{

	}

	template <typename S>
	T getData(S key)
	{

	}

};


#endif