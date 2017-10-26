#pragma once
template<typename T>
struct Node
{
	T* data;
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
	Node<T>* CopyList(const DoublyLinkedList&);
public:
	DoublyLinkedList();
	DoublyLinkedList(const DoubleLinkedList&);
	DoublyLinkedList& operator=(const DoubleLinkedList&);
	~DoublyLinkedList();

	bool Push_Back(const T&);
	bool Insert(const T&, int);
	bool Remove(int);
	bool Empty() const { return m_First; }
	T& Pop_Back();
	T& Head();
	T& Tail();
	int Size() const;
};
template<typename T>
Node<T>* DoublyLinkedList<T>::CopyList(const DoublyLinkedList& rhs)
{
	if (!rhs.Empty())
	{
		Node<T>* oursCurrent,* theirsCurrent,* oursPrevious = nullptr;
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
	}
}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : m_Size(0), m_First(nullptr), m_Last(nullptr) 
{

}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoubleLinkedList& rhs)
{
	Node<T>* current = rhs.m_First->next;
	m_First = new Node<T>(rhs.m_First->data, nullptr, current);
	m_Last = m_First;
	while (current)
	{
		current = new Node<T>(current->data, )
	}
}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList& operator=(const DoubleLinkedList&);
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList();

template<typename T>
bool DoublyLinkedList<T>::Push_Back(const T&);
template<typename T>
bool DoublyLinkedList<T>::Insert(const T&, int);
template<typename T>
bool DoublyLinkedList<T>::Remove(int);
template<typename T>
bool DoublyLinkedList<T>::IsEmpty() const;
template<typename T>
T& DoublyLinkedList<T>::Pop_Back();
template<typename T>
T& DoublyLinkedList<T>::Head();
template<typename T>
T& DoublyLinkedList<T>::Tail();
template<typename T>
int DoublyLinkedList<T>::Size() const;