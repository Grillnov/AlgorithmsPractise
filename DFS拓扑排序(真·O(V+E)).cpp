#include <iostream>
#include <list>
using namespace std;

void TopologicalSort(int(*Graph)[6], unsigned verts)
{
	int* stacker = new int[verts];
	int currentTop = -1;
	int* isAvailable = new int[verts];
	int* Res = new int[verts];
	unsigned Verts_to_go = verts;
	memset((void*)isAvailable, 0, sizeof(int)*verts);
	for (register unsigned i = 0; i != verts; ++i)
	{
		if (isAvailable[i] != 0)
			continue;
		isAvailable[i] = 1;
		++currentTop;
		stacker[currentTop] = i;
		while (currentTop != -1)
		{
			unsigned Cur = stacker[currentTop];
			bool isOver = true;
			int ptr = Graph[Cur][0];
			int j = 0;
			while (ptr != -1)
			{
				++j;
				if (isAvailable[ptr] == 0)
				{
					++currentTop;
					isAvailable[ptr] = 1;
					stacker[currentTop] = ptr;
					isOver = false;
					break;
				}
				ptr = Graph[Cur][j];
			}
			if (isOver)
			{
				--currentTop;
				--Verts_to_go;
				Res[Verts_to_go] = Cur;
			}
		}
	}

	for (unsigned i = 0; i != verts; ++i)
	{
		cout << Res[i] << endl;
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