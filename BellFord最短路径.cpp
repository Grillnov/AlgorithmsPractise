#include <iostream>
#include <vector>
using namespace std;
struct Edge
{
	unsigned target;
	double weight;
	Edge(unsigned tar, double wei) :target(tar), weight(wei){};
};
bool BellFord(vector<Edge> *Graph, unsigned vertices, unsigned source)
{
	double* ResDistance = new double[vertices];
	for (int i = 0; i != vertices; ++i)
	{
		ResDistance[i] = INFINITY;
	}
	ResDistance[source] = 0.0;
	for (int i = 0; i != vertices - 1; ++i)
	{
		for (int j = 0; j != vertices; ++j)
		{
			for (auto E : Graph[j])
			{
				double RelaxVal = E.weight + ResDistance[j];
				if (ResDistance[E.target] > RelaxVal)
					ResDistance[E.target] = RelaxVal;
			}
		}
	}
	for (int i = 0; i != vertices; ++i)
	{
		cout << ResDistance[i] << endl;
	}
	for (int j = 0; j != vertices; ++j)
	{
		for (auto E : Graph[j])
		{
			double RelaxVal = E.weight + ResDistance[j];
			if (ResDistance[E.target] > RelaxVal)
				return false;
		}
		return true;
	}
}
int main()
{
	vector<Edge> Graph[6];
	Graph[0] = { Edge(1, 5), Edge(2, 3) };
	Graph[1] = { Edge(2, 2), Edge(3, 6) };
	Graph[2] = { Edge(3, 7), Edge(4, 4), Edge(5, 2) };
	Graph[3] = { Edge(4, -1), Edge(5, 1) };
	Graph[4] = { Edge(5, -2) };
	Graph[5] = {};
	BellFord(Graph, 6, 1);
}