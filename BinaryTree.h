#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
template<typename T>
struct Node
{
	T data;
	Node<T>* leftChild;
	Node<T>* rightChild;
	Node(const T& key = T()) : data(key),leftChild(nullptr),rightChild(nullptr) {}
};
template<typename T>
class BinaryTree
{
private:
	Node<T>* m_Root;
	void CopyTree(Node<T>*&, const Node<T>*);
	void DeleteTree(Node<T>*&);
	Node<T>*& LeftRotation(Node<T>*&);
	Node<T>*& RightRotation(Node<T>*&);
	Node<T>*& LeftRightRotation(Node<T>*&);
	Node<T>*& RightLeftRotation(Node<T>*&);
	void Balance(Node<T>*&);
	bool m_Balanced;
public:
	BinaryTree(Node<T>*);
	BinaryTree(const BinaryTree<T>&);
	BinaryTree<T>& operator=(const BinaryTree<T>&);
	void Insert(Node<T>*&, const T&);
	void Delete(Node<T>*&, const T&);
	Node<T>*& MinNode(Node<T>*&);
	~BinaryTree();
	void TurnBalance(bool expression) { m_Balanced = expression; }
	void GetLeafs(Node<T>*, std::vector<Node<T>*>&) const;
	Node<T>* Search(Node<T>*, const T&);
	void CrossSection(Node<T>*, Node<T>*, BinaryTree<T>&);
	void PrintLevels(Node<T>*) const;
	void PrintLeftRootRight(Node<T>*) const;
	Node<T>* SmallestAncestor(Node<T>*,const T&, const T&) const;
	int Height(Node<T>* = GetRoot()) const;
	Node<T>* GetRoot() const { return m_Root; }
};

template<typename T>
void BinaryTree<T>::CopyTree(Node<T>*& root, const Node<T>* rhs)
{
	if (rhs)
	{
		root = new Node<T>;
		root->data = rhs->data;
		CopyTree(root->leftChild, rhs->leftChild);
		CopyTree(root->rightChild, rhs->rightChild);
	}
}
template<typename T>
void BinaryTree<T>::DeleteTree(Node<T>*& root)
{
	if (root)
	{
		DeleteTree(root->leftChild);
		DeleteTree(root->rightChild);
		delete root;
		root = nullptr;
	}
}
template<typename T>
Node<T>*& BinaryTree<T>::LeftRotation(Node<T>*& root)
{
	Node<T>* newRoot = root->rightChild;
	root->rightChild = newRoot->leftChild;
	newRoot->leftChild = root;
	return newRoot;
}
template<typename T>
Node<T>*& BinaryTree<T>::RightRotation(Node<T>*& root)
{
	Node<T>* newRoot = root->leftChild;
	root->leftChild = newRoot->rightChild;
	newRoot->rightChild = root;
	return newRoot;
}
template<typename T>
Node<T>*& BinaryTree<T>::LeftRightRotation(Node<T>*& root)
{
	root->rightChild = RightRotation(root->rightChild);
	return LeftRotation(root);
}
template<typename T>
Node<T>*& BinaryTree<T>::RightLeftRotation(Node<T>*& root)
{
	root->leftChild = LeftRotation(root->leftChild);
	return RightRotation(root);
}
template<typename T>
void BinaryTree<T>::Balance(Node<T>*& root)
{
	if (root && m_Balanced)
	{
		//if right subtre is heavier than rightsubtree
		if (Height(root->rightChild) - Height(root->leftChild) > 1)
		{
			if (Height(root->rightChild->leftChild) - Height(root->rightChild->rightChild) >= 1)
			{
				root = LeftRightRotation(root);
			}
			else
			{
				root = LeftRotation(root);
			}
		}
		//if left subtree is heavier than rightsubtree
		else if (Height(root->leftChild) - Height(root->rightChild) > 1)
		{
			if (Height(root->leftChild->rightChild) - Height(root->leftChild->leftChild) >= 1)
			{
				root = RightLeftRotation(root);
			}
			else
			{
				root = RightRotation(root);
			}
		}
	Balance(root->leftChild);
	Balance(root->rightChild);
	}
}
template<typename T>
BinaryTree<T>::BinaryTree(Node<T>* root) : m_Root(root), m_Balanced(true)
{

}
template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& rhs)
{
	CopyTree(m_Root,rhs.m_Root);
	m_Balanced = rhs->m_Balanced;
}
template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& rhs)
{
	if (this != &rhs)
	{
		m_Balanced = rhs->m_Balanced;
		DeleteTree(m_Root);
		CopyTree(m_Root, rhs.m_Root);
	}
	return *this;
}
template<typename T>
void BinaryTree<T>::Insert(Node<T>*& root, const T& key)
{
	if (root)
	{
		if (root->data > key)
		{
			Insert(root->leftChild, key);
		}
		else
		{
			Insert(root->rightChild, key);
		}
	}
	else
	{
		root = new Node<T>(key);
	}
	Balance(root);
}
template<typename T>
void BinaryTree<T>::Delete(Node<T>*& root, const T& key)
{
	if (!root) return;
	if (root->data < key)
	{
		Delete(root->rightChild, key);
	}
	else if (root->data > key)
	{
		Delete(root->leftChild, key);
	}
	else
	{
		if (!root->leftChild)
		{
			Node<T>* temp = root->rightChild;
			delete root;
			root = temp;
			return;
		}
		else if (!root->rightChild)
		{
			Node<T>* temp = root->leftChild;
			delete root;
			root = temp;
			return;
		}
		Node<T>* temp = MinNode(root->rightChild);
		root->data = temp->data;
		Delete(root->rightChild, temp->data);
	}
	Balance(root);
}
template<typename T>
BinaryTree<T>::~BinaryTree()
{
	DeleteTree(m_Root);
}
template<typename T>
int BinaryTree<T>::Height(Node<T>* rhs) const
{
	if (!rhs)
	{
		return -1;
	}
	return Height(rhs->rightChild) > Height(rhs->leftChild) ?
		Height(rhs->rightChild) + 1 : Height(rhs->leftChild) + 1;
}
template<typename T>
void BinaryTree<T>::PrintLevels(Node<T>* root) const
{
	std::queue<Node<T>*> wave;
	wave.push(root);
	while (!wave.empty())
	{
		for (int i = wave.size(); i > 0; --i)
		{
			Node<T>* temp = wave.front();
			wave.pop();
			if (temp->leftChild) wave.push(temp->leftChild);
			if (temp->rightChild) wave.push(temp->rightChild);
			std::cout << temp->data << ' ';
		}
		std::cout << std::endl;
	}
}
template<typename T>
void BinaryTree<T>::PrintLeftRootRight(Node<T>* root) const
{
	if (root)
	{
		PrintLeftRootRight(root->leftChild);
		std::cout << root->data << ' ';
		PrintLeftRootRight(root->rightChild);
	}
}
template<typename T>
void BinaryTree<T>::GetLeafs(Node<T>* root, std::vector<Node<T>*>& vector) const
{
	if (!root) return;
	GetLeafs(root->leftChild, vector);
	GetLeafs(root->rightChild, vector);
	if (!root->leftChild && !root->rightChild)
		vector.push_back(root);
}
template<typename T>
void BinaryTree<T>::CrossSection(Node<T>* lhs, Node<T>* rhs, BinaryTree<T>& tree)
{
	if (lhs && rhs)
	{
		tree.Insert(tree.GetRoot(), lhs->data);
		CrossSection(lhs->leftChild, rhs->leftChild, tree);
		CrossSection(lhs->rightChild, rhs->rightChild, tree);
	}
}
template<typename T>
Node<T>*& BinaryTree<T>::MinNode(Node<T>*& root)
{
	if (root)
	{
		MinNode(root->leftChild);
	}
	return root;
}
template<typename T>
Node<T>* BinaryTree<T>::SmallestAncestor(Node<T>* root, const T& first, const T& second) const
{
	if (!root) return nullptr;
	if (first > second) return SmallestAncestor(root, second, first);
	if (first <= root->data && root->data <= second) return root;
	if (second < root->data) return SmallestAncestor(root->leftChild, first, second);
	return SmallestAncestor(root->rightChild, first, second);
}
template<typename T>
Node<T>* BinaryTree<T>::Search(Node<T>* root, const T& key)
{
	if (!root) return nullptr;
	if (root->data == key) return root;
	if (root->data < key) return Search(root->rightChild, key);
	return Search(root->leftChild, key);
}