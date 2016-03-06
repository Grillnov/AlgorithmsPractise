#include <iostream>
using namespace std;
int main(void)
{
	int k = 0;
	scanf("%d", &k);
	for (int i = 0; i != k; ++i)
	{
		int n = 0;
		scanf("%d", &n);
		int* strP = new int[n];
		for (unsigned j = 0; j != n; ++j)
		{
			scanf("%d", strP + j);
		}
		int lastIndex = 0;
		int stackTop = -1;
		int usedTimes = 0;
		int* beg = new int[n];
		
		for (unsigned j = 0; j != n; ++j)
		{
			int enStacked = strP[j] - lastIndex;
			lastIndex = strP[j];
			while (enStacked > 0)
			{
				--enStacked;
				++stackTop;
				beg[stackTop] = usedTimes;
				++usedTimes;
			}
			++usedTimes;
			int end = usedTimes;
			printf("%d ", (end - beg[stackTop]) / 2);
			--stackTop;
		}
		printf("\n");
	}
}