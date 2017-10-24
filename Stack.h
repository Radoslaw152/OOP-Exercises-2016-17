#pragma once
#pragma once
#include <iostream>
template<typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node(const T& _data = T(), Node<T>* _next = nullptr) : data(_data), next(_next) {}
};
template<typename T>
class Stack
{
private:
	Node<T>* m_Head;
	int m_Size;
	void CopyStack(const Stack& rhs);
	void DeleteStack();
public:
	Stack(const T& Head = T(), int size = 0);
	Stack(const Stack&);
	Stack<T>& operator=(const Stack&);
	~Stack();
	bool Empty() const { return m_Size == 0; }
	void PushBack(const T&);
	T PopBack();
	T Top();
	int Size() const { return m_Size; }
};
template<typename T>
void Stack<T>::CopyStack(const Stack& rhs)
{
	if (!rhs.Empty())
	{
		Node<T>* lastCopied,* copyFrom,* bufferNode;
		lastCopied = new Node<T>(rhs.m_Head->data);
		copyFrom = rhs.m_Head->next;
		m_Head = lastCopied;
		while (copyFrom)
		{
			bufferNode = new Node<T>(copyFrom->data);
			lastCopied->next = bufferNode;
			copyFrom = copyFrom->next;
		}
	}
}
template<typename T>
void Stack<T>::DeleteStack()
{
	while (!Empty())
		PopBack();
	m_Size = 0;
}
template<typename T>
Stack<T>::Stack(const T& Head, int size) : m_Head(new Node<T>(Head, nullptr)), m_Size(size)
{

}
template<typename T>
Stack<T>::Stack(const Stack& rhs)
{
	CopyStack(rhs);
}
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if (this != &rhs)
	{
		DeleteStack();
		CopyStack(rhs);
	}
	return *this;
}
template<typename T>
Stack<T>::~Stack()
{
	DeleteStack();
}
template<typename T>
void Stack<T>::PushBack(const T& element)
{
	Node<T>* newElement = new Node<T>(element, m_Head);
	m_Head = newElement;
	m_Size++;
}
template<typename T>
T Stack<T>::PopBack()
{
	if (!m_Head)
	{
		std::cout << "Error: Popping back from empty stack!" << std::endl;
		return T();
	}
	Node<T>* nodeToDelete = m_Head;
	m_Head = m_Head->next;
	T data = nodeToDelete->data;
	delete[] nodeToDelete;
	m_Size--;
	return data;
}
template<typename T>
T Stack<T>::Top()
{
	if (!Empty())
	{
		return m_Head->data;
	}
	return T();
}