#include <iostream>
#include "Graph.h"

struct Vertex
{
	int V;
	int W;
	bool operator==(const Vertex& rhs) const
	{
		return V == rhs.V;
	}
	bool operator==(int a) const
	{
		return V == a;
	}
	bool operator!=(const Vertex& rhs) const
	{
		return !(*this == rhs);
	}
	Vertex(const int v, const int w) : V(v), W(w) {}
};
class WeightedGraph : public Graph<Vertex>
{
public:
	int LongestPathInDAG();
};
int WeightedGraph::LongestPathInDAG()
{
	if (HasLoop())
		return -1;
	std::vector<Vertex> wave = TopologicalSorting();
	std::vector<int> Distance(wave.size());
	for (int i = 0; i < Distance.size(); ++i)
	{
		Distance[i] = -1;
	}
	Distance[wave[0].V - 1] = wave[0].W;
	int MaxPath = 0;
	for (int i = 0; i < wave.size(); ++i)
	{
		Vertex temp = wave[i];
		std::list<std::list<Vertex>>::iterator it = m_Graph.begin();
		while (temp != *it->begin())
			++it;
		std::list<Vertex>::iterator secondIt = it->begin();
		secondIt++;
		if (secondIt == it->end())
		{
			Distance[it->begin()->V - 1] = it->begin()->W;
			if (MaxPath < Distance[it->begin()->V - 1])
				MaxPath = Distance[it->begin()->V - 1];
		}
		if (secondIt != it->end() && Distance[temp.V - 1] != -1)
		{
			while (secondIt != it->end())
			{
				if (Distance[secondIt->V - 1] < Distance[it->begin()->V - 1] + secondIt->W)
				{
					Distance[secondIt->V - 1] = Distance[it->begin()->V - 1] + secondIt->W;
					if (MaxPath < Distance[secondIt->V - 1])
						MaxPath = Distance[secondIt->V - 1];
				}
				secondIt++;
			}
		}
	}
	return MaxPath;
}

int main()
{
	WeightedGraph graph;
	graph.AddVertex(Vertex(1,5));
	graph.AddVertex(Vertex(2, 2));
	graph.AddVertex(Vertex(3, 7));
	graph.AddVertex(Vertex(4, 11));
	graph.AddVertex(Vertex(5, 9));
	graph.AddVertex(Vertex(6, 2));
	graph.AddVertex(Vertex(7, 40));
	graph.AddEdge(Vertex(1, 5), Vertex(2, 2));
	graph.AddEdge(Vertex(1, 5), Vertex(3, 7));
	graph.AddEdge(Vertex(2, 2), Vertex(4, 11));
	graph.AddEdge(Vertex(3, 7), Vertex(5, 9));
	graph.AddEdge(Vertex(4, 11), Vertex(6, 2));
	graph.AddEdge(Vertex(5, 9), Vertex(6, 2));
	graph.AddEdge(Vertex(6, 2), Vertex(7, 40));
	std::cout << graph.LongestPathInDAG() << std::endl;
	return 0;
}