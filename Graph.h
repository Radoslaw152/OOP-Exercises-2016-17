#pragma once
#include <list>
#include <vector>
#include <stack>
#include <queue>
template<typename T>
class Graph
{
private:
	std::list<std::list<T>> m_Graph;
	static bool Check(const std::vector<T>&, const T&);
public:
	bool CheckVertex(const T&);
	bool CheckEdge(const T&, const T&);
	bool AddVertex(const T&);
	bool RemoveVertex(const T&);
	bool AddEdge(const T&, const T&);
	bool RemoveEdge(const T&, const T&);
	void Print();



	std::vector<T> TopologicalSorting();
	int ShortestWay(const T&, const T&);
	bool HasLoop();
};
template<typename T>
std::ifstream& operator >> (std::ifstream& is, const Graph<T>& rhs)
{
	int Vertexes, Edges;
	is >> Vertexes >> Edges;
	for (int i = 0; i < Vertexes; ++i)
	{
		T temp;
		is >> temp;
		rhs.AddVertex(temp);
	}
	for (int i = 0; i < Edges; ++i)
	{
		T first, second;
		is >> first >> second;
		rhs.AddEdge(first, second);
	}
	return is;
}
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
template<typename T>
bool Graph<T>::CheckEdge(const T& a, const T& b)
{
	std::list<std::list<T>>::iterator it = m_Graph.begin();
	while (it != m_Graph.end() && *it->begin() != a)
		it++;
	if (it == m_Graph.end()) return false;
	std::list<T>::iterator secondIt = it->begin();
	while (secondIt != it->end() && *secondIt != b)
		secondIt++;
	if (secondIt == it->end()) return false;
	return true;
}
template<typename T>
std::vector<T> Graph<T>::TopologicalSorting() 
{
	std::vector<T> sortedElements;
	std::stack<T> wave;
	std::vector<T> checked;
	checked.push_back(*(m_Graph.begin())->begin());
	wave.push(*(m_Graph.begin())->begin());
	while (!wave.empty())
	{
		T current = wave.top();
		wave.pop();
		std::list<std::list<T>>::iterator it = m_Graph.begin();
		while (*it->begin() != current)
			it++;
		std::list<T>::iterator secondIt = it->begin();
		secondIt++;

		bool addCurrent = true;
		while (secondIt != it->end())
		{
			if (!Check(checked,*secondIt))
			{
				if (addCurrent)
				{
					wave.push(current);
					addCurrent = false;
				}
				checked.push_back(*secondIt);
				wave.push(*secondIt);
			}
			secondIt++;
		}
		if(addCurrent)
			sortedElements.insert(sortedElements.begin(),current);
		if (wave.empty() && sortedElements.size() < m_Graph.size())
		{
			std::list<std::list<T>>::iterator it = m_Graph.begin();
			while (it != m_Graph.end())
			{
				if (!Check(checked, *it->begin()))
				{
					wave.push(*it->begin());
					checked.push_back(*it->begin());
				}
				it++;
			}
		}
	}
	return sortedElements;
}
template<typename T>
int Graph<T>::ShortestWay(const T& a, const T& b)
{
	std::queue<T> wave;
	wave.push(a);
	std::vector<T> checked;
	checked.push_back(a);
	int sum = 0;
	while (!wave.empty())
	{
		T current = wave.front();
		wave.pop();
		std::list<std::list<T>>::iterator it = m_Graph.begin();
		while (it != m_Graph.end() && *it->begin() != current)
			++it;
		if (it == m_Graph.end()) return -1;
		std::list<T>::iterator secondIt = it->begin();
		secondIt++;
		while (secondIt != it->end())
		{
			if (*secondIt == b)
			{
				return sum;
			}
			if (!Check(checked, *secondIt))
			{
				wave.push(*secondIt);
				checked.push_back(*secondIt);
			}
			secondIt++;
		}
		++sum;
	}
	return -1;
}
template<typename T>
bool Graph<T>::HasLoop()
{
	std::vector<T> wave;
	std::vector<T> checked;
	checked.push_back(*(m_Graph.begin())->begin());
	wave.push_back(*(m_Graph.begin())->begin());
	while (!wave.empty())
	{
		T current = wave.back();
		wave.pop_back();
		std::list<std::list<T>>::iterator it = m_Graph.begin();
		while (*it->begin() != current)
			it++;
		std::list<T>::iterator secondIt = it->begin();
		secondIt++;

		bool addCurrent = true;
		while (secondIt != it->end())
		{
			if (Check(wave, *secondIt))
				return true;
			if (!Check(checked, *secondIt))
			{
				if (addCurrent)
				{
					wave.push_back(current);
					addCurrent = false;
				}
				checked.push_back(*secondIt);
				wave.push_back(*secondIt);
			}
			secondIt++;
		}
		if (wave.empty())
		{
			std::list<std::list<T>>::iterator it = m_Graph.begin();
			while (it != m_Graph.end())
			{
				if (!Check(checked, *it->begin()))
				{
					wave.push_back(*it->begin());
					checked.push_back(*it->begin());
				}
				it++;
			}
		}
	}
	return false;
}
template<typename T>
 bool Graph<T>::Check(const std::vector<T>& vector, const T& key)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		if (vector[i] == key)
			return true;
	}
	return false;
}