#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

void TopologicalSort(vector<int> *Graph, int vertices)
{
	int *inStatus = new int[vertices];
	memset(reinterpret_cast<void*>(inStatus), 0, vertices*sizeof(int));
	for (int i = 0; i != vertices; ++i)
	{
		for (auto a : Graph[i])
		{
			++inStatus[a];
		}
	}
	for (int i = 0; i != vertices; ++i)
	{
		for (int j = 0; j != vertices; ++j)
		{
			if (inStatus[j] == -1)
			{
				continue;
			}
			if (inStatus[j] == 0)
			{
				inStatus[j] = -1;
				cout << j << endl;
				for (auto a : Graph[j])
				{
					--inStatus[a];
				}
				break;
			}
		}
	}
}

int main()
{
	vector<int> v1[6];
	v1[0] = { 2, 3 };
	v1[2] = { 3, 4 };
	v1[3] = { 5, 1, 4 };
	v1[5] = { 1, 4 };
	v1[4] = {};
	TopologicalSort(v1, 6);
	//cout << static_cast<double>(clock()) / CLOCKS_PER_SEC << endl;
}