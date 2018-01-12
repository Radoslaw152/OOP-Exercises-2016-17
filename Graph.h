#pragma once
#include <list>

template<typename T>
class Graph
{
private:
	std::list<std::list<T>> m_Graph;
public: 
	bool AddVertex(const T&);
	bool RemoveVertex(const T&);
	bool AddEdge(const T&, const T&);
	bool RemoveEdge(const T&, const T&);
	std::list<std::list<T>>::iterator GetVertex(const T&);
	std::list<T>::iterator GetEdge(const T&, const T&);
};
template<typename T>
bool Graph<T>::AddVertex(const T& key)
{

}
template<typename T>
bool Graph<T>::RemoveVertex(const T&)
{

}
template<typename T>
bool Graph<T>::AddEdge(const T&, const T&)
{

}
template<typename T>
bool Graph<T>::RemoveEdge(const T&, const T&)
{

}
template<typename T>
std::list<std::list<T>>::iterator Graph<T>::GetVertex(const T& key)
{
	std::list<std::list<T>>::iterator it = m_Graph.begin();
	while (it != m_Graph.end() && *it.front() == key)
		it++;
	return it;
}
template<typename T>
std::list<T>::iterator Graph<T>::GetEdge(const T& a, const T& b)
{
	std::list<T>::iterator it = GetVertex(a).begin();
	while (*it != b)
		++it;
}