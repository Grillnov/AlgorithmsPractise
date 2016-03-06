#include <iostream>
using namespace std;
int N;
char cows[2000];
char ans[2000];
int main(void)
{
	cin >> N;
	for (unsigned i = 0; i != N; ++i)
	{
		cin >> cows[i];
	}
	int init = 0;
	int tail = N - 1;
	int curIndex = 0;
	while (init != tail)
	{
		if (cows[init] < cows[tail])
		{
			ans[curIndex] = cows[init];
			++init;
		}
		else if (cows[init]>cows[tail])
		{
			ans[curIndex] = cows[tail];
			--tail;
		}
		else
		{
			int markl = init;
			int markr = tail;
			while (cows[markl] == cows[markr] && markl != markr)
			{
				++markl;
				--markr;
			}
			if (cows[markl] < cows[markr])
			{
				ans[curIndex] = cows[init];
				++init;
			}
			else
			{
				ans[curIndex] = cows[tail];
				--tail;
			}
		}
		++curIndex;
	}
	ans[curIndex] = cows[init];
	int ptr = 0;
	for (unsigned i = 0; i != N; ++i)
	{
		cout << ans[i];
		++ptr;
		if (ptr % 80 == 0 && i < N - 1)
			cout << endl;
	}
	cout << endl;
}