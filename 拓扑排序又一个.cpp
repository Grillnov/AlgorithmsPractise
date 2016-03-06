#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <time.h>

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
	if (ResultSet.size() != vertices)
		return false;
	else
		return true;
}


int main()
{
	vector<int> v1[6];
	v1[0] = { 2, 3 };
	v1[1] = { 4 };
	v1[2] = { 3, 4 };
	v1[3] = { 5, 1, 4 };
	v1[5] = { 1, 4 };
	v1[4] = {};
	TopologicalSort(v1, 6);
	//cout << static_cast<double>(clock()) / CLOCKS_PER_SEC << endl;
}