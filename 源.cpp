#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
using namespace std;

struct Edge
{
	unsigned target;
	double weight;
	Edge(unsigned tar, double wei) :target(tar), weight(wei){}
};

void BFS(vector<Edge>* Graph, unsigned vertices, unsigned source)
{
	char *isAvailable = new char[vertices];
	memset((void*)isAvailable, 0, sizeof(char)*vertices);
	queue<unsigned> Container;
	Container.push(source);
	isAvailable[source] = 1;
	while (!Container.empty())
	{
		unsigned Cur = Container.front();
		cout << Cur << endl;
		Container.pop();
		for (auto E : Graph[Cur])
		{
			if (isAvailable[E.target] == 0)
			{
				isAvailable[E.target] = 1;
				Container.push(E.target);
			}
		}
	}
}

void DFS(vector<Edge>* Graph, unsigned vertices)
{
	char *isAvailable = new char[vertices];
	memset((void*)isAvailable, 0, sizeof(char)*vertices);
	stack<unsigned> Container;
	for (int i = 0; i != vertices; ++i)
	{
		if (isAvailable[i] == 0)
		{
			Container.push(i);
			isAvailable[i] = 1;
			cout << i << endl;
			while (!Container.empty())
			{
				bool isOver = true;
				unsigned Cur = Container.top();
				for (auto a : Graph[Cur])
				{
					if (isAvailable[a.target] == 0)
					{
						isOver = false;
						isAvailable[a.target] = 1;
						Container.push(a.target);
						cout << a.target << endl;
						break;
					}
				}
				if (isOver)
				{
					Container.pop();
				}
			}
		}
	}
}

bool Topo(unsigned* Graph, unsigned vertices)
{
	char *isAvailable = new char[vertices];
	memset((void*)isAvailable, 0, sizeof(char)*vertices);
	stack<unsigned> Container;
	list<unsigned> Solution;
	for (int i = 0; i != vertices; ++i)
	{
		if (isAvailable[i] != 0)
			continue;
		isAvailable[i] = 1;
		Container.push(i);
		while (!Container.empty())
		{
			bool isOver = true;
			for (int j = 0; j != vertices; ++j)
			{
				unsigned Cur = Container.top();
				if (Graph[Cur*vertices + j] != 0 && isAvailable[j] == 0)
				{
					isOver = false;
					isAvailable[j] = 1;
					Container.push(j);
				}
			}
			if (isOver)
			{
				unsigned CurFin = Container.top();
				Solution.push_front(CurFin);
				Container.pop();
			}
		}
	}
	for (auto a : Solution)
	{
		cout << a << endl;
	}
	if (Solution.size() != vertices)
		return true;
	else
		return false;
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
	//DFS(Graph, 6);
	unsigned Graph1[] =
	{
		0, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 1, 1, 1,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 0
	};
	Topo(Graph1, 6);
}