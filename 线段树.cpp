#include <iostream>
using namespace std;
struct intervalNode
{
	int lower;
	int upper;
	int val;
	intervalNode(){};
	intervalNode(int val, int lower, int upper)
		:lower(lower), val(val), upper(upper){};
};

intervalNode intervalTree[65536];
int valTable[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

int buildTree(int lower, int upper, int serial = 0)
{
	if (lower == upper)
	{
		intervalTree[serial].val = valTable[lower - 1];
		intervalTree[serial].lower = lower;
		intervalTree[serial].upper = upper;
		return valTable[lower - 1];
	}
	else
	{
		intervalTree[serial].lower = lower;
		intervalTree[serial].upper = upper;
		int leftval = buildTree(lower, (lower + upper) / 2, 2 * serial + 1);
		int rightval = buildTree((lower + upper) / 2 + 1, upper, 2 * serial + 2);
		int answer = leftval + rightval;
		intervalTree[serial].val = answer;
		return answer;
	}
}

int tot = 0;
void traverseTree(int lower, int upper, int serial = 0)
{
	if ((intervalTree[serial].upper<lower) || (intervalTree[serial].lower>upper))
		return;
	if ((intervalTree[serial].lower >= lower) && (intervalTree[serial].upper <= upper))
	{
		tot += intervalTree[serial].val;
		return;
	}
	traverseTree(lower, upper, 2 * serial + 1);
	traverseTree(lower, upper, 2 * serial + 2);
}

int main(void)
{
	buildTree(1, 9, 0);
	traverseTree(1, 8, 0);
	cout << tot;
}