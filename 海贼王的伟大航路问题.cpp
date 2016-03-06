#include <iostream>
using namespace std;

int res[16384][16];
int graph[16][16];
int verts;

int solve(unsigned short set, int source)
{
	int minVal = 1 << 30;
	for (unsigned i = 1; i != verts - 1; ++i)
	{
		if (!(set&(1 << (i - 1))))
			continue;
		if (i == source)
			continue;
		int curVal = res[set ^ (1 << (i - 1))][i];
		if (curVal == -1)
			curVal = solve(set ^ (1 << (i - 1)), i);
		int newVal = curVal + graph[source][i];
		if (newVal < minVal)
			minVal = newVal;
	}
	res[set][source] = minVal;
	return minVal;
}

int main(void)
{
	cin >> verts;
	for (unsigned i = 0; i != 16384; ++i)
	{
		for (unsigned j = 0; j != 16; ++j)
		{
			res[i][j] = -1;
		}
	}
	for (unsigned i = 0; i != verts; ++i)
	{
		for (unsigned j = 0; j != verts; ++j)
		{
			cin >> graph[i][j];
		}
	}
	for (unsigned i = 0; i != verts - 1; ++i)
	{
		res[0][i] = graph[i][verts - 1];
	}
	unsigned short set = 0;
	for (unsigned i = 1; i != (verts - 1); ++i)
	{
		set |= (1 << (i - 1));
	}
	cout << solve(set, 0);
}