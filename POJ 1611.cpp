#include <iostream>
#include <string.h>
using namespace std;
int n, m;
int pred[30000];
int sum[30000];

int getParent(int src)
{
	int ptrsrc = src;
	while (ptrsrc != pred[ptrsrc])
	{
		ptrsrc = pred[ptrsrc];
	}
	pred[src] = ptrsrc;
	return ptrsrc;
}

void Merge(int one, int another)
{
	int srcone = getParent(one);
	int srcanother = getParent(another);
	if (srcanother == srcone)
	{
		return;
	}
	sum[srcone] += sum[srcanother];
	pred[srcanother] = srcone;
}

int main(void)
{
	while (true)
	{
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;
		for (unsigned i = 0; i != n; ++i)
		{
			pred[i] = i;
			sum[i] = 1;
		}
		for (unsigned i = 0; i != m; ++i)
		{
			int k, h;
			cin >> k >> h;
			for (unsigned j = 1; j != k; ++j)
			{
				int curStudent;
				cin >> curStudent;
				Merge(h, curStudent);
			}
		}
		cout << sum[getParent(0)] << endl;
	}
}