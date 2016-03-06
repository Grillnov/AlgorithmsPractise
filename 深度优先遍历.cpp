#include <iostream>
#include <stack>
#include <list>
static unsigned timesStackUsed = 0;
using namespace std;

struct BegFin
{
	unsigned begin;
	unsigned end;
};

list<BegFin> L;

void DFS(int* Graph, int vertices)
{
	int* Status = new int[vertices];
	BegFin* df = new BegFin[vertices];
	for (int i = 0; i != vertices; ++i)
	{
		Status[i] = 0;
	}
	stack<int> Container;
	for (int i = 0; i != vertices; ++i)
	{
		if (Status[i] != 0)
			continue;
		Container.push(i);
		++timesStackUsed;
		df[i].begin = timesStackUsed;
		cout << i << endl;
		Status[i] = 1;
		while (!Container.empty())
		{
			bool isOver = true;
			int Cur = Container.top();
			for (int k = 0; k != vertices; ++k)
			{
				if (Graph[Cur*vertices + k] != 0 && Status[k] == 0)
				{
					isOver = false;
					Container.push(k);
					++timesStackUsed;
					df[k].begin = timesStackUsed;
					cout << k << endl;
					Status[k] = 1;
					break;
				}
			}
			if (isOver)
			{
				int Cur = Container.top();
				Container.pop();
				++timesStackUsed;
				df[Cur].end = timesStackUsed;
			}
		}
	}
	for (int i = 0; i != vertices; ++i)
	{
		L.push_back(df[i]);
	}
	delete[] df;
}

int main(void)
{
	int SimpleGraph[25] =
	{ 
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 1,
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 1, 0, 0, 0 
	};
	DFS(SimpleGraph, 5);
	for (auto a : L)
	{
		cout << a.begin << '/' << a.end << endl;
	}
}