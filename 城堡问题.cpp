#include <iostream>
#include <stack>

using namespace std;

struct pair1
{
	int i;
	int j;
	pair1(int i, int j) :i(i), j(j){};
};

int main(void)
{
	int m;
	int n;
	cin >> m >> n;
	int answer = 0;
	int maxVal = 0;
	char* status = new char[m*n];
	char* graph = new char[m*n];

	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != n; ++j)
		{
			int val;
			cin >> val;
			graph[i*n + j] = val;
			status[i*n + j] = 0;
		}
	}
	
	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != n; ++j)
		{
			if (status[i*n + j] != 0)
				continue;
			++answer;
			status[i*n + j] = 1;
			int currentVal = 1;
			stack<pair1> container;
			container.push(pair1(i, j));
			while (!container.empty())
			{
				bool isOver = true;
				pair1 cur = container.top();
				char wallstatus = graph[cur.i*n + cur.j];
				if (!(wallstatus & 0x1))
				{
					if (status[cur.i*n + cur.j - 1] == 0)
					{
						isOver = false;
						status[cur.i*n + cur.j - 1] = 1;
						++currentVal;
						container.push(pair1(cur.i, cur.j - 1));
						continue;
					}
				}
				if (!(wallstatus & 0x2))
				{
					if (status[(cur.i - 1)*n + cur.j] == 0)
					{
						isOver = false;
						status[(cur.i - 1)*n + cur.j] = 1;
						++currentVal;
						container.push(pair1(cur.i - 1, cur.j));
						continue;
					}
				}
				if (!(wallstatus & 0x4))
				{
					if (status[cur.i*n + cur.j + 1] == 0)
					{
						isOver = false;
						status[cur.i*n + cur.j + 1] = 1;
						++currentVal;
						container.push(pair1(cur.i, cur.j + 1));
						continue;
					}
				}
				if (!(wallstatus & 0x8))
				{
					if (status[(cur.i + 1)*n + cur.j] == 0)
					{
						isOver = false;
						status[(cur.i + 1)*n + cur.j] = 1;
						++currentVal;
						container.push(pair1(cur.i + 1, cur.j));
						continue;
					}
				}
				if (isOver)
				{
					container.pop();
					if (currentVal > maxVal)
						maxVal = currentVal;
				}
			}
		}
	}
	cout << answer << endl << maxVal;
	return 0;
}