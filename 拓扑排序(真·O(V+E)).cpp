#include <iostream>

void TopologicalSort(int (*graph)[6], unsigned verts)
{
	int* Res = new int[verts];
	int* isAvailable = new int[verts];
	int* inDegree = new int[verts];
	for (unsigned register i = 0; i != verts; ++i)
	{
		isAvailable[i] = 0;
		inDegree[i] = 0;
	}
	for (unsigned register i = 0; i != verts; ++i)
	{
		int ptr = graph[i][0];
		int cur = 0;
		while (ptr != -1)
		{
			++inDegree[ptr];
			++cur;
			ptr = graph[i][cur];
		}
	}
	unsigned zeroIndegree = -1;
	unsigned register k = 0;
	for (k = 0; k != verts; ++k)
	{
		if (inDegree[k] == 0)
		{
			zeroIndegree = k;
			break;
		}
	}
	if (k == verts)
	{
		std::cout << "Cycle detected" << std::endl;
		return;
	}
	unsigned Vertsleft = verts;
	while (Vertsleft > 0)
	{
		Res[verts - Vertsleft] = zeroIndegree;
		unsigned nextzeroIndegree = zeroIndegree;
		isAvailable[zeroIndegree] = 1;
		int ptr = graph[zeroIndegree][0];
		int cur = 0;
		while (ptr != -1)
		{
			--inDegree[ptr];
			if (inDegree[ptr] == 0 && isAvailable[ptr] == 0)
			{
				nextzeroIndegree = ptr;
			}
			++cur;
			ptr = graph[zeroIndegree][cur];
		}
		zeroIndegree = nextzeroIndegree;
		--Vertsleft;
	}
	for (unsigned i = 0; i != verts; ++i)
	{
		std::cout << Res[i] << std::endl;
	}
}

int main(void)
{
	/*int Graph[] =
	{
		0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 1, 0,
		0, 0, 0, 1, 0, 1,
		0, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 1, 0
	};*/
	int Graph[6][6]=
	{
		{ 2, 3, -1 },
		{ 4, -1 },
		{ 3, 4, -1 },
		{ 1, 4, 5, -1 },
		{ -1 },
		{ 1, 4, -1 }
	};
	TopologicalSort(Graph, 6);
}