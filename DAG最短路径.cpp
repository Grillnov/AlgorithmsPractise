#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <time.h>

struct Edge
{
	int target;
	double weight;
	Edge(int target, double weight) :target(target), weight(weight){}
};

using namespace std;

bool TopologicalSort(vector<int> *Graph, int vertices)
{
	list<int> ResultSet;
	int* Status = new int[vertices];
	memset((void*)(Status), 0, sizeof(int)*vertices);
	stack<int> Container;
	for (int i = 0; i != vertices; ++i)
	{
		if (Status[i] != 0)
			continue;
		Container.push(i);
		Status[i] = 1;
		while (!Container.empty())
		{
			bool isOver = true;
			int Cur = Container.top();
			for (auto a : Graph[Cur])
			{
				if (Status[a] == 0)
				{
					isOver = false;
					Container.push(a);
					//cout << a << endl;
					Status[a] = 1;
					break;
				}
			}
			if (isOver)
			{
				int Cur = Container.top();
				Container.pop();
				ResultSet.push_front(Cur);
			}
		}
	}
	for (auto a : ResultSet)
	{
		cout << a << endl;
	}
	delete[] Status;
	if (ResultSet.size() != vertices)
		return false;
	else
		return true;
}

void DAG(vector<Edge> *Graph, int vertices, int Source)
{
	list<int> ResultSet;
	int* Status = new int[vertices];
	double* ResWeight = new double[vertices];
	memset((void*)(Status), 0, sizeof(int)*vertices);
	for (int i = 0; i != vertices; ++i)
	{
		ResWeight[i] = INFINITY;
	}
	ResWeight[Source] = 0.0;
	stack<int> Container;
	for (int i = 0; i != vertices; ++i)
	{
		if (Status[i] != 0)
			continue;
		Container.push(i);
		Status[i] = 1;
		while (!Container.empty())
		{
			bool isOver = true;
			int Cur = Container.top();
			for (auto a : Graph[Cur])
			{
				if (Status[a.target] == 0)
				{
					isOver = false;
					Container.push(a.target);
					//cout << a << endl;
					Status[a.target] = 1;
					break;
				}
			}
			if (isOver)
			{
				int Cur = Container.top();
				Container.pop();
				ResultSet.push_front(Cur);
			}
		}
	}
	
	for (auto a : ResultSet)
	{
		for (auto E : Graph[a])
		{
			if (ResWeight[E.target] > ResWeight[a] + E.weight)
				ResWeight[E.target] = ResWeight[a] + E.weight;
		}
	}
	delete[] Status;
	for (int i = 0; i != vertices; ++i)
	{
		cout << ResWeight[i] << endl;
	}
	delete[] ResWeight;
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
	DAG(Graph, 6, 1);
	//cout << static_cast<double>(clock()) / CLOCKS_PER_SEC << endl;
}