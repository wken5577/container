#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>
#include <iostream>
#include "pair.hpp"
#include <exception>


namespace ft
{

typedef enum NodeType
{
    NRed = 0,
    NBlack,
	NDummy
} NodeType;

template <typename KEY, typename VAL, typename T=ft::pair<KEY, VAL>, class Compare = std::less<KEY> , class Allocator = std::allocator<T> > 
class RBTree
{
    struct TNode
    {
    public:
        T 				*data;
        NodeType 		type;
        TNode 			*parent;
        TNode 			*left;
        TNode 			*right;

    public:
		TNode()
		:data(nullptr), type(NDummy), parent(nullptr), left(nullptr), right(nullptr)
		{
		}

        TNode(T *data, NodeType type)
        :data(data), type(type), parent(nullptr), left(nullptr), right(nullptr)
        {}

        friend bool operator<( const TNode& lhs, const TNode& rhs)
        {
            return Compare(lhs.data->first, rhs.data->first);
        }
    };

public:
   typedef T        *dataType;
   typedef TNode    *node;

private:
    TNode 	        *head;
    Compare         _comp;
    Allocator       _alloc;

    TNode *makeNewNode(T data, NodeType type)
    {
        T *dataPointer = _alloc.allocate(1);
        dataPointer->first = data.first;
        dataPointer->second = data.second;
        return new TNode(dataPointer, type);
    }


    void insertNewRedNode(TNode *existData, TNode *newNode)
    {
        TNode *tar = existData;
        TNode *parent = existData->parent;
        TNode *sameNode = nullptr;
        searchNode(head, &sameNode, newNode->data->first);
        if (sameNode)
        {
            _alloc.destroy(sameNode->data);
            _alloc.deallocate(sameNode->data, 1);
            sameNode->data= newNode->data;
            delete newNode;
            return;
        }
        
        while (tar)
        {
            if (tar && _comp(newNode->data->first, tar->data->first))
            {
                parent = tar;
                tar = tar->left;
            } else if (tar && _comp(tar->data->first, newNode->data->first))
            {
                parent = tar;
                tar = tar->right;
            }
        }
        newNode->parent = parent;
        if (_comp(newNode->data->first, parent->data->first))
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    void insertNewRedNode(TNode *newNode)
    {
        TNode *tar = head;
        TNode *parent = head->parent;
        TNode *sameNode = nullptr;
        searchNode(head, &sameNode, newNode->data->first);
        if (sameNode)
        {
            _alloc.destroy(sameNode->data);
            _alloc.deallocate(sameNode->data, 1);
            sameNode->data= newNode->data;
            delete newNode;
            return;
        }
        
        while (tar)
        {
            if (tar && _comp(newNode->data->first, tar->data->first))
            {
                parent = tar;
                tar = tar->left;
            } else if (tar && _comp(tar->data->first, newNode->data->first))
            {
                parent = tar;
                tar = tar->right;
            }
        }
        newNode->parent = parent;
        if (_comp(newNode->data->first, parent->data->first))
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    template <typename S>
    void    searchNode(TNode *head, TNode **tar, S key)
    {
        if (!head)
            return;
        if (head->data->first == key)
        {
            *tar = head;
            return;
        }
        searchNode(head->left, tar, key);
        searchNode(head->right, tar, key);
    }

    void searchDoubleRedNode(TNode *head, TNode **tar)
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
        searchDoubleRedNode(head->left, tar);
        searchDoubleRedNode(head->right, tar);
    }

    TNode *isDoubleRed()
    {
        TNode *tar = nullptr;
        searchDoubleRedNode(head, &tar);
        return tar;
    }

    void linkRestructData(TNode  **nodeList, TNode *p,TNode *n)
    {
        if (p->left == n)
        {
            nodeList[2]->left = nodeList[1]->right;
            if (nodeList[1]->right)
                nodeList[1]->right->parent = nodeList[2];
        }
        else
        {
            nodeList[0]->right = nodeList[1]->left;
            if (nodeList[1]->left)
                nodeList[1]->left->parent = nodeList[0];
        }
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
                if (_comp(nodeList[j + 1]->data->first, nodeList[j]->data->first))
                {
                    tmp = nodeList[j + 1];
                    nodeList[j + 1] = nodeList[j];
                    nodeList[j] = tmp;
                }
            }
        }
        linkRestructData(nodeList, p, n);
        nodeList[1]->parent = gp;
        if (!gp)
            head = nodeList[1];
        if (gp && _comp(nodeList[1]->data->first, gp->data->first))
            gp->left = nodeList[1];
        else if (gp && _comp(gp->data->first, nodeList[1]->data->first))
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

    void checkDoubleRed()
    {
        TNode *dblRedTarget = isDoubleRed();
        while (dblRedTarget)
        {
            doRestructRecoloring(dblRedTarget);
            dblRedTarget = isDoubleRed();
        }
    }

    void deleteHeadNode(TNode *target, NodeType deleteType)
    {
        if (!target->left && !target->right)
        {
            _alloc.destroy(target->data);
            _alloc.deallocate(target->data, 1);
            delete target;
            head = nullptr;
        }
        else if ((target->left && !target->right) || (!target->left && target->right))
        {
            if (target->left)
            {
                target->left->parent = nullptr;
                head = target->left;
            }
            else
            {
                target->right->parent = nullptr;
                head = target->right;
            }
            _alloc.destroy(target->data);
            _alloc.deallocate(target->data, 1);
            delete target;
        }
        else
        {
            TNode *tmp = target->right;
            while (tmp->left)
                tmp = tmp->left;
            T *dataPointer = _alloc.allocate(1);
            dataPointer->first = tmp->data->first;
            dataPointer->second = tmp->data->second;
            _alloc.destroy(target->data);
            _alloc.deallocate(target->data, 1);
            target->data = dataPointer;
            deleteOneNode(tmp, tmp->type);
        }
        if (deleteType == NBlack)
        {
            if(head->type == NRed)
                head->type = NBlack;
        }
    }

    void rotateLeft(TNode *siblings)
    {
        TNode *p = siblings->parent;
        TNode *gp = p->parent;
        TNode *left = siblings->left;

        siblings->parent = gp;
        siblings->left = p;
        p->right = left;
        p->parent = siblings;
        if (left)
            left->parent = p;
        if (p == head)
            head = siblings;
        if (gp && gp->left == p)
            gp->left = siblings;
        else if (gp && gp->right == p)
            gp->right = siblings;
    }

    void rotateRight(TNode *siblings)
    {
        TNode *p = siblings->parent;
        TNode *gp = p->parent;
        TNode *right = siblings->right;

        siblings->parent = gp;
        siblings->right = p;
        p->left = right;
        p->parent = siblings;
        if (right)
            right->parent = p;
        if (p == head)
            head = siblings;
        if (gp && gp->left == p)
            gp->left = siblings;
        else if (gp && gp->right == p)
            gp->right = siblings;
    }


    bool case4(bool left, TNode *sibling, TNode *p, TNode *sr, TNode *sl)
    {
        if (left && sibling->type == NBlack && sr && sr->type == NRed)
        {
            sibling->type = p->type;
            sibling->right->type = NBlack;
            p->type = NBlack;
            rotateLeft(sibling);
            return true;
        }
        else if (!left && sibling->type == NBlack && sl && sl->type == NRed)
        {
            sibling->type = p->type;
            sibling->left->type = NBlack;
            p->type = NBlack;
            rotateRight(sibling);
            return true;
        }
        return false;
    }

    bool case3(bool left, TNode *sibling, TNode *p, TNode *sr, TNode *sl)
    {
        if (left && sibling->type == NBlack && sl && sl->type == NRed && (!sr || sr->type == NBlack))
        {
            sibling->type = NRed;
            sl->type = NBlack;
            rotateRight(sibling->left);
            return true;
        }
        else if (!left && sibling->type == NBlack && sr && sr->type == NRed && (!sl || sl->type == NBlack))
        {
            sibling->type = NRed;
            sr->type = NBlack;
            rotateLeft(sibling->right);
            return true;
        }
        return false;
    }

    bool case2(bool left, TNode *sibling, TNode *p, TNode *sr, TNode *sl)
    {
        if (left && sibling->type == NBlack && (!sl || sl->type == NBlack) && (!sr || sr->type == NBlack))
        {
            sibling->type = NRed;
            controlExtraBlack(p, NBlack);
            return true;
        }
        else if (!left && sibling->type == NBlack && (!sl || sl->type == NBlack) && (!sr || sr->type == NBlack))
        {
            sibling->type = NRed;
            controlExtraBlack(p, NBlack);
            return true;
        }
        return false;
    }

    bool case1(bool left, TNode *sibling, TNode *p, TNode *sr, TNode *sl)
    {
        if (sibling->type == NRed)
        {
            TNode* doublyBlackNode = p->left;
            if (!left)
                doublyBlackNode = p->right;
            sibling->type = NBlack;
            p->type = NRed;
            if (left)
                rotateLeft(sibling);
            else
                rotateRight(sibling);
            controlExtraBlack(doublyBlackNode, NBlack);
            return true;
        }
        return false;
    }

    void controlExtraBlack(TNode *node, NodeType deleteType)
    {
        TNode *sibling = (node->parent->left == node) ? node->parent->right : node->parent->left;
        TNode *p = node->parent;
        TNode *sr = sibling->right;
        TNode *sl = sibling->left;
        bool left = (p->left == node) ? true : false;
    
        if (deleteType == NBlack)
        {
            if (node->type == NRed)
                node->type = NBlack;
            else
            {
                //doubly black control
                if (case4(left, sibling, p, sr, sl))
                    return;
                if (case3(left, sibling, p, sr, sl))
                {
                    sibling = (node->parent->left == node) ? node->parent->right : node->parent->left;
                    p = node->parent;
                    sr = sibling->right;
                    sl = sibling->left;
                    case4(left, sibling, p, sr, sl);
                    return;
                }
                if (case2(left, sibling, p, sr, sl))
                    return;
                if (case1(left, sibling, p, sr, sl))
                    return;
            }
        }
    }

    void deleteOneNode(TNode *target, NodeType deleteType)
    {
        if (target == head)
        {
            deleteHeadNode(target, deleteType);
            return;
        }
        TNode *p = target->parent;
        if (!target->left && !target->right && deleteType == NRed)
        {
            if (p->left == target)
                p->left = nullptr;
            else
                p->right = nullptr;
            _alloc.destroy(target->data);
            _alloc.deallocate(target->data, 1);
            delete target;
        }
        else if (!target->left && !target->right && deleteType == NBlack)
        {
            controlExtraBlack(target, deleteType);
            if (p->left == target)
                p->left = nullptr;
            else
                p->right = nullptr;
            _alloc.destroy(target->data);
            _alloc.deallocate(target->data, 1);
            delete target;
        }
        else if ((target->left && !target->right) || (!target->left && target->right))
        {
            if (target->left)
            {
                target->left->parent = p;
                if (p->left == target)
                    p->left = target->left;
                else
                    p->right = target->left;
                controlExtraBlack(target->left, deleteType);
            }
            else
            {
                target->right->parent = p;
                if (p->left == target)
                    p->left = target->right;
                else
                    p->right = target->right;
                controlExtraBlack(target->right, deleteType);
            }
            _alloc.destroy(target->data);
            _alloc.deallocate(target->data, 1);
            delete target;
        }
        else
        {
            TNode *tmp = target->right;
            while (tmp->left)
                tmp = tmp->left;
            T *dataPointer = _alloc.allocate(1, dataPointer);
            dataPointer->first = tmp->data->first;
            dataPointer->second = tmp->data->second;
            _alloc.destroy(target->data);
            _alloc.deallocate(target->data, 1);
            target->data = dataPointer;
            deleteOneNode(tmp, tmp->type);
        }
    }

    void startDelete(TNode *head)
    {
        if (!head)
            return;
        if (head->left)
            startDelete(head->left);
        if (head->right)
            startDelete(head->right);
		if (head->type != NDummy)
		{
			_alloc.destroy(head->data);
        	_alloc.deallocate(head->data, 1);
		}
        delete head;
    }

	void insertDummy()
	{
		if (!head)
			return;
		TNode *minDummy = new TNode();
		TNode *maxDummy = new TNode();

		TNode *tmp = head;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = minDummy;
		minDummy->parent = tmp;

		tmp = head;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = maxDummy;
		maxDummy->parent = tmp;
	}

	void deleteDummy()
	{
		if (!head)
			return;
		TNode *tmp = head;
		while (tmp->left)
			tmp = tmp->left;
		if (tmp->type == NDummy)
		{
			tmp->parent->left = nullptr;
			delete tmp;
		}

		tmp = head;
		while (tmp->right)
			tmp = tmp->right;
		if (tmp->type == NDummy)
		{
			tmp->parent->right = nullptr;
			delete tmp;
		}
	}

    void countNode(size_t *num, TNode *head)
    {
        if (!head)
            return;
        if (head->left)
            countNode(head->left);
        if (head->right)
            countNode(head->right);
        (*num)++;
    }

public:
    RBTree()
    :head(nullptr)
    {}

    RBTree(Compare comp)
    :head(nullptr), _comp(comp)
    {}

    RBTree(const RBTree &data)
    {
        *this = data;
    }

    RBTree& operator=(const RBTree &data)
    {
        this->head = data.head;
        return *this;
    }

    ~RBTree()
    {
        deleteAllData();
    }

    void deleteAllData()
    {
        startDelete(this->head);
        this->head = nullptr;
    }

    void printRBTree(TNode *head)
    {
        if(!head || head->type == NDummy)
            return;
        printRBTree(head->left);
        std::cout << head->data->first << " " <<  head->data->second << " ";
        if (head->type == NBlack)
            std::cout << "Black" << "\n";
        else
            std::cout << "Red" << "\n";
        printRBTree(head->right);
    }

    node getNode(T data)
    {
        deleteDummy();
        node target = nullptr;
        searchNode(head, &target, data.first);
        insertDummy();
        return target;
    }

    template<typename K>
    node getNodeByKey(K key)
    {
        deleteDummy();
        node target = nullptr;
        searchNode(head, &target, key);
        insertDummy();
        return target;
    }

    void insertNode(T data)
    {
        if (!head)
        {
            TNode *newNode = makeNewNode(data, NBlack);
            head = newNode;
			insertDummy();
            return ;
        }
		deleteDummy();
        TNode *newNode = makeNewNode(data, NRed);
        insertNewRedNode(newNode);
        checkDoubleRed();
		insertDummy();
    }

    void insertNode(T existData, T data)
    {
        deleteDummy();
        TNode *newNode = makeNewNode(data, NRed);
        insertNewRedNode(existData, newNode);
        checkDoubleRed();
		insertDummy();
    }

    template <typename S>
    void deleteNode(S key)
    {
		deleteDummy();
        TNode *target = nullptr;
        searchNode(head, &target, key);
        if (!target)
            return;
        NodeType deleteType;
        if ((!target->left && !target->right) || (!target->left && target->right) || (target->left && !target->right))
            deleteType = target->type;
        else
        {
            TNode *tmp = target->right;
            while (tmp->left)
                tmp = tmp->left;
            deleteType = tmp->type;
        }
        deleteOneNode(target, deleteType);
		insertDummy();
    }

    template <typename S>
    dataType getData(S key)
    {
		deleteDummy();
        TNode *target = nullptr;
        searchNode(head, &target, key);
		insertDummy();
        if (!target)
            throw NoSuchDataExcepton();
        return target->data;
    }

    TNode *getTreeHead()
    {
        return this->head;
    }

	TNode *getFirst()
	{
		if (!head)
			return nullptr;
		TNode *tmp = head;
		while (tmp->left)
			tmp = tmp->left;
		return tmp;
	}

	TNode *getLast()
	{
		if (!head)
			return nullptr;
		TNode *tmp = head;
		while (tmp->right)
			tmp = tmp->right;
		return tmp;
	}

    size_t getSize()
    {
        size_t num = 0;
        countNode(&num, head);
        return num;
    }

    class NoSuchDataExcepton : public std::exception
    {
        const char* what() const throw()
        {
            return "no such data exists!";
        }
    };

};


};


#endif