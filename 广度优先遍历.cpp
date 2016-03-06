#include <iostream>
#include <queue>
using namespace std;
void BFS(int *Graph, int vertices, int source)
{
	int* Status = new int[vertices];
	for (int i = 0; i != vertices; ++i)
	{
		Status[i] = 0;
	}
	queue<int> Container;
	Container.push(source);
	while (!Container.empty())
	{
		int Now = Container.front();
		Status[Now] = 1;
		cout << Now << endl;
		Container.pop();
		bool vertEnd = true;
		for (int i = 0; i != vertices; ++i)
		{
			int Cur = Graph[Now*vertices + i];
			if (Cur != 0 && Status[i] == 0)
			{
				Status[i] = 1;
				Container.push(i);
				vertEnd = false;
			}
		}
		if (vertEnd)
		{
			Status[Now] = 2;
		}
	}
}

int main()
{
	int SimpleGraph[25] =
	{ 0, 1, 1, 1, 0,
	1, 0, 0, 0, 0,
	1, 0, 0, 0, 1,
	1, 0, 0, 0, 0,
	0, 0, 1, 0, 0 };
	BFS(SimpleGraph, 5, 0);
}