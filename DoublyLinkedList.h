#pragma once
template<typename T>
struct Node
{
	T data;
	Node<T>* previous;
	Node<T>* next;
	Node(T _data = T(), Node<T>* _previous = nullptr, Node<T>* _next = nullptr)
		: data(_data), previous(_previous), next(_next) {}
};
template<typename T>
class DoublyLinkedList
{
private:
	Node<T>* m_First;
	Node<T>* m_Last;
	int m_Size;
	void CopyList(const DoublyLinkedList&); 
public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList&);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList&);
	~DoublyLinkedList();
	T& operator[](int); //Allows to modify the data of a Node
	bool Push_Back(const T&); //Adds an element as a last node
	bool Insert(const T&, int); //Adds an element before the index
	//a.k.a. the new element will be with index i
	bool Remove(int); //Removes an element with index i
	bool Empty() const { return m_Size == 0; }
	T Pop_Back(); //removes the last element, and returns it
	T Head(); //Gives the last element
	T Tail(); //Gives the fist element
	int Size() const; //Returns the size of the list
	void DeleteList(); //Destoys the list
	void Swap(int, int); //Swaps the data of two nodes
};
template<typename T>
void DoublyLinkedList<T>::CopyList(const DoublyLinkedList& rhs)
{
	if (!rhs.Empty())
	{
		Node<T>* oursCurrent,* theirsCurrent;
		m_First = new Node<T>(rhs.m_First->data);
		oursCurrent = m_First;
		theirsCurrent = rhs.m_First->next;
		while (theirsCurrent)
		{
			oursCurrent->next = new Node<T>(theirsCurrent->data);
			oursCurrent->previous = oursCurrent;
			oursCurrent = oursCurrent->next;
			theirsCurrent = theirsCurrent->next;
		}
		m_Last = oursCurrent->previous;
		m_Size = rhs.m_Size;
	}
}
template<typename T>
void DoublyLinkedList<T>::DeleteList()
{
	Node<T>* toDelete = m_First;
	Node<T>* useToDelete = nullptr;
	while (toDelete)
	{
		useToDelete = toDelete;
		toDelete = toDelete->next;
		delete useToDelete;
	}
	m_First = nullptr;
	m_Last = nullptr;
	m_Size = 0;
}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : m_Size(0), m_First(nullptr), m_Last(nullptr) 
{

}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& rhs)
{
	CopyList(rhs);
}
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& rhs)
{
	if (this != &rhs)
	{
		DeleteList();
		CopyList(rhs);
	}
}
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	DeleteList();
}
template<typename T>
bool DoublyLinkedList<T>::Push_Back(const T& key)
{
	Node<T>* newElement = new Node<T>(key, m_Last);
	if (!newElement)
		return false;
	if (!m_First) 
	{
		m_First = newElement;
		m_First->previous = nullptr;
		m_First->next = m_Last;
		m_Last = newElement;
		m_Last->previous = m_First;
	}
	else
	{
		if (m_Size == 1)
		{
			m_First->next = newElement;
		}
		m_Last->next = newElement;
		m_Last = newElement;
	}
	m_Size++;
	return true;
}
template<typename T>
bool DoublyLinkedList<T>::Insert(const T& key, int n)
{
	if (n < 0 || (n > m_Size && n != 0))
	{
		std::cerr << "Error: cannot insert in this position";
		return false;
	}
	if (n == 0)
	{
		Node<T>* newElement = new Node<T>(key, nullptr, m_First);
		m_First->previous = newElement;
		m_First = newElement;
		return ++m_Size;
	}
	if (n == m_Size)
	{
		Node<T>* newElement = new Node<T>(key, m_Last);
		if (m_Size == 1)
		{
			m_First->next = newElement;
		}
		m_Last->next = newElement;
		m_Last = newElement;
		return ++m_Size;
	}
	Node<T>* current = m_First;
	for (int currentPlace = 0; currentPlace < n; currentPlace++)
		current = current->next;
	Node<T>* newElement = new Node<T>(key, current->previous, current);
	current->previous->next = newElement;
	current->previous = newElement;
	return ++m_Size;
}
template<typename T>
bool DoublyLinkedList<T>::Remove(int n)
{
	if (n < 0 || (n > m_Size - 1 && n != 0))
	{
		std::cerr << "Error: cannot remove in this position";
		return false;
	}
	if (n == 0)
	{
		Node<T>* deleteElement = m_First;
		m_First = m_First->next;
		if(m_First)
			m_First->previous = nullptr;
		delete deleteElement;
		return --m_Size;
	}
	if (n == m_Size - 1)
	{
		if (m_Size == 1)
		{
			m_First = nullptr;
		}
		Node<T>* deleteElement = m_Last;
		m_Last = m_Last->previous;
		m_Last->next = nullptr;
		delete deleteElement;
		return --m_Size;
	}
	Node<T>* toDelete = m_First;
	for (int currentPlace = 0; currentPlace < n; currentPlace++)
		toDelete = toDelete->next;
	Node<T>* newElement = toDelete->previous;
	newElement->next = toDelete->next;
	if(toDelete->next)
		toDelete->next->previous = newElement;
	delete toDelete;
	return --m_Size;
}

template<typename T>
T DoublyLinkedList<T>::Pop_Back()
{
	if (Empty())
	{
		std::cerr << "Error: cannot pop back";
		return T();
	}
	T data = m_Last->data;
	Remove(m_Size - 1);
	return data;
}
template<typename T>
T DoublyLinkedList<T>::Head()
{
	if (Empty())
	{
		std::cerr << "Error: cannot give head";
		return T();
	}
	T data = m_Last->data;
	return data;
}
template<typename T>
T DoublyLinkedList<T>::Tail()
{
	if (Empty())
	{
		std::cerr << "Error: cannot give tail";
		return T();
	}
	T data = m_First->data;
	return data;
}

template<typename T>
int DoublyLinkedList<T>::Size() const
{
	return m_Size;
}
template<typename T>
T& DoublyLinkedList<T>::operator[](int n)
{
	if (n > m_Size - 1)
	{
		std::cerr << "Error: cannot use operator []";
		T n = 0;
		return n;
	}
	Node<T>* current = m_First;
	for (int currentPlace = 0; currentPlace < n; currentPlace++)
		current = current->next;
	return current->data;
}
template<typename T>
void DoublyLinkedList<T>::Swap(int a, int b)
{
	if (a != b && a > -1 && a < m_Size && b > -1 && b < m_Size)
	{
		Node<T>* first = m_First;
		for (int currentPlace = 0; currentPlace < a; currentPlace++)
			first = first->next;
		Node<T>* second = m_First;
		for (int currentPlace = 0; currentPlace < b; currentPlace++)
			second = second->next;
		T temp = first->data;
		first->data = second->data;
		second->data = temp;
	}
}