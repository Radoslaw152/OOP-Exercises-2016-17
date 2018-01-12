#pragma once
#include <list>

template<typename T>
class Graph
{
private:
	std::list<std::list<T>> m_Graph;
	bool CheckVertex(const T&);
public:
	bool AddVertex(const T&);
	bool RemoveVertex(const T&);
	bool AddEdge(const T&, const T&);
	bool RemoveEdge(const T&, const T&);
	void Print();
};
template<typename T>
void Graph<T>::Print()
{
	std::list<std::list<T>>::iterator it = m_Graph.begin();
	while (it != m_Graph.end())
	{
		std::list<T>::iterator secondIt = it->begin();
		while (secondIt != it->end())
		{
			std::cout << *secondIt << " ";
			secondIt++;
		}
		std::cout << std::endl;
		it++;
	}
}
template<typename T>
bool Graph<T>::CheckVertex(const T& key)
{
	std::list<std::list<T>>::iterator it = m_Graph.begin();
	while (it != m_Graph.end())
	{
		if (*it->begin() == key)
			return true;
		it++;
	}
	return false;
}
template<typename T>
bool Graph<T>::AddVertex(const T& key)
{
	if (CheckVertex(key))
	{
		return false;
	}
	std::list<T> temp;
	temp.push_back(key);
	m_Graph.push_back(temp);
	return true;
}
template<typename T>
bool Graph<T>::RemoveVertex(const T& key)
{
	std::list<std::list<T>>::iterator it = m_Graph.begin();
	bool haveDeletedSomething = false;
	while (it != m_Graph.end())
	{
		bool isDeleted = false;
		std::list<T>::iterator secondIterator = it->begin();
		while (secondIterator != it->end())
		{
			if (secondIterator == it->begin() && *secondIterator == key)
			{
				m_Graph.erase(it);
				it = m_Graph.begin();
				haveDeletedSomething = true;
				isDeleted = true;
				break;
			}
			if (*secondIterator == key)
			{
				it->erase(secondIterator);
				break;
			}
			secondIterator++;
		}
		if (!isDeleted)
		{
			it++;
		}
	}
	return haveDeletedSomething;
}
template<typename T>
bool Graph<T>::AddEdge(const T& a, const T& b)
{
	std::list<std::list<T>>::iterator it = m_Graph.begin();
	while (it != m_Graph.end() && *it->begin() != a)
	{
		T temp = *it->begin();
		it++;
	}
	if (it == m_Graph.end()) 
	{ 
		return false; 
	}
	std::list<T>::iterator secondIt = it->begin();
	while (secondIt != it->end())
	{
		if (*secondIt == b)
		{
			return false;
		}
		secondIt++;
	}
	it->push_back(b);
	return true;
}
template<typename T>
bool Graph<T>::RemoveEdge(const T& a, const T& b)
{
	std::list<std::list<T>>::iterator it = m_Graph.begin();
	while (it != m_Graph.end() && *it->begin() != a)
		it++;
	if (it == m_Graph.end()) return false;
	std::list<T>::iterator secondIt = it->begin();
	while (secondIt != it->end() && *secondIt != b)
		secondIt++;
	if (secondIt == it->end())
		return false;
	it->erase(secondIt);
	return true;
}
