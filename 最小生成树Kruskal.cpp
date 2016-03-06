#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <unordered_set>
using namespace std;
struct Edge
{
	unsigned u;
	unsigned v;
	double weight;
	Edge(){};
	Edge(unsigned u, unsigned v, double w) :u(u), v(v), weight(w)
	{};
	bool operator<(const Edge& rhs)
	{
		return (this->weight < rhs.weight);
	}
};

double minSpanningTree(double* Graph, unsigned vertices)
{
	vector<Edge> temp;
	temp.reserve((vertices*vertices - vertices) / 2);
	for (int i = 0; i != vertices; ++i)
	{
		for (int j = i + 1; j != vertices; ++j)
		{
			temp.push_back(Edge(i, j, Graph[i*vertices + j]));
		}
	}
	sort(temp.begin(), temp.end());
	int* status = new int[vertices];
	for (int i = 0; i != vertices; ++i)
	{
		status[i] = i;
	}
	double totWeight = 0.0;
	unsigned edgesInTree = 0;
	for (int i = 0; i != temp.size(); ++i)
	{
		int uTree = 0, vTree = 0;
		for (uTree = temp[i].u; status[uTree] != uTree; uTree = status[uTree])//判断线段的起始点所在的集合
			status[uTree] = status[status[uTree]];
		for (vTree = temp[i].v; status[vTree] != vTree; vTree = status[vTree])//判断线段的终点所在的集合
			status[vTree] = status[status[vTree]];
		if (uTree != vTree)
		{
			totWeight += temp[i].weight;
			status[vTree] = status[uTree];
			++edgesInTree;
			cout << temp[i].u << '\\' << temp[i].v << endl;
			if (edgesInTree == vertices - 1)
				break;
		}
	}
	return totWeight;
}

const static double Inf = 500;

int main()
{
	double Graph[] =
	{
		0, 4, Inf, Inf, Inf, Inf, Inf, 8, Inf,
		4, 0, 8, Inf, Inf, Inf, Inf, 11, Inf,
		Inf, 8, 0, 7, Inf, 4, Inf, Inf, 2,
		Inf, Inf, 7, 0, 9, 14, Inf, Inf, Inf,
		Inf, Inf, Inf, 9, 0, 10, Inf, Inf, Inf,
		Inf, Inf, 4, 14, 10, 0, 2, Inf, Inf,
		Inf, Inf, Inf, Inf, Inf, 2, 0, 1, 6,
		8, 11, Inf, Inf, Inf, Inf, 1, 0, 7,
		Inf, Inf, 2, Inf, Inf, Inf, 6, 7, 0
	};
	cout << minSpanningTree(Graph, 9) << endl;
	cout << static_cast<double>(clock()) / CLOCKS_PER_SEC << endl;
	double Graph2[] =
	{
		0, 3, 2, 1,
		3, 0, 4, Inf,
		2, 4, 0, 7,
		1, Inf, 7, 0
	};
	cout << minSpanningTree(Graph2, 4) << endl;
}