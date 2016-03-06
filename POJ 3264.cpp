#include <stdio.h>
//using namespace std;

struct node
{
	int lower;
	int upper;
	int minVal;
	int maxVal;
};

node tree[200000];
int val[50000];

void buildTree(int lower, int upper, int serial)
{
	if (lower == upper)
	{
		tree[serial].lower = lower;
		tree[serial].upper = upper;
		int curVal = val[upper];
		tree[serial].maxVal = curVal;
		tree[serial].minVal = curVal;
		return;
	}
	int curMax, curMin;
	buildTree(lower, (lower + upper) / 2, 2 * serial + 1);
	buildTree((lower + upper) / 2 + 1, upper, 2 * serial + 2);
	int resLeftmax = tree[2 * serial + 1].maxVal;
	int resRightmax = tree[2 * serial + 2].maxVal;
	int resLeftmin = tree[2 * serial + 1].minVal;
	int resRightmin = tree[2 * serial + 2].minVal;
	curMax = resLeftmax > resRightmax ? resLeftmax : resRightmax;
	curMin = resLeftmin < resRightmin ? resLeftmin : resRightmin;
	tree[serial].lower = lower;
	tree[serial].upper = upper;
	tree[serial].maxVal = curMax;
	tree[serial].minVal = curMin;
	return;
}

int maxVal = 0, minVal = 1 << 30;

void traverse(int lower, int upper, int serial)
{
	if (tree[serial].lower >= lower&&tree[serial].upper <= upper)
	{
		if (tree[serial].minVal < minVal)
			minVal = tree[serial].minVal;
		if (tree[serial].maxVal>maxVal)
			maxVal = tree[serial].maxVal;
		return;
	}
	int mid = (tree[serial].lower + tree[serial].upper) / 2;
	if (upper <= mid)
	{
		traverse(lower, upper, serial * 2 + 1);
	}
	else if (lower > mid)
	{
		traverse(lower, upper, serial * 2 + 2);
	}
	else
	{
		traverse(lower, upper, serial * 2 + 1);
		traverse(lower, upper, serial * 2 + 2);
	}
}

int N, Q;
int main(void)
{
	scanf("%d %d", &N, &Q);
	for (unsigned i = 0; i != N; ++i)
	{
		scanf("%d", &val[i]);
	}
	buildTree(0, N - 1, 0);
	for (unsigned i = 0; i != Q; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		traverse(a - 1, b - 1, 0);
		printf("%d\n", maxVal - minVal);
		maxVal = 0;
		minVal = 1 << 30;
	}
}