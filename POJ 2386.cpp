#include <iostream>
#include <stack>
using namespace std;

int N, M;
char land[100][100];
char status[100][100];

struct pair1
{
	int i;
	int j;
	pair1(int i, int j) : i(i), j(j){};
};

int main(void)
{
	cin >> N >> M;
	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != M; ++j)
		{
			cin >> land[i][j];
			status[i][j] = 0;
		}
	}
	int answer = 0;
	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != M; ++j)
		{
			if (land[i][j] == '.')
				continue;
			if (status[i][j] != 0)
				continue;
			++answer;
			stack<pair1> container;
			container.push(pair1(i, j));
			status[i][j] = 1;
			while (!container.empty())
			{
				pair1 cur = container.top();
				container.pop();
				if (cur.i - 1 >= 0 && land[cur.i - 1][cur.j] == 'W')
				{
					if (status[cur.i - 1][cur.j] == 0)
					{
						status[cur.i - 1][cur.j] = 1;
						container.push(pair1(cur.i - 1, cur.j));
					}
				}
				if (cur.i - 1 >= 0 && cur.j - 1 >= 0 && land[cur.i - 1][cur.j - 1] == 'W')
				{
					if (status[cur.i - 1][cur.j - 1] == 0)
					{
						status[cur.i - 1][cur.j - 1] = 1;
						container.push(pair1(cur.i - 1, cur.j - 1));
					}
				}
				if (cur.j - 1 >= 0 && land[cur.i][cur.j - 1] == 'W')
				{
					if (status[cur.i][cur.j - 1] == 0)
					{
						status[cur.i][cur.j - 1] = 1;
						container.push(pair1(cur.i, cur.j - 1));
					}
				}
				if (cur.i + 1 < N&&cur.j - 1 >= 0 && land[cur.i + 1][cur.j - 1] == 'W')
				{
					if (status[cur.i + 1][cur.j - 1] == 0)
					{
						status[cur.i + 1][cur.j - 1] = 1;
						container.push(pair1(cur.i + 1, cur.j - 1));
					}
				}
				if (cur.i + 1 < N&&land[cur.i + 1][cur.j] == 'W')
				{
					if (status[cur.i + 1][cur.j] == 0)
					{
						status[cur.i + 1][cur.j] = 1;
						container.push(pair1(cur.i + 1, cur.j));
					}
				}
				if (cur.i + 1 < N&&cur.j + 1 < M&&land[cur.i + 1][cur.j + 1] == 'W')
				{
					if (status[cur.i + 1][cur.j + 1] == 0)
					{
						status[cur.i + 1][cur.j + 1] = 1;
						container.push(pair1(cur.i + 1, cur.j + 1));
					}
				}
				if (cur.j + 1 < M&&land[cur.i][cur.j + 1] == 'W')
				{
					if (status[cur.i][cur.j + 1] == 0)
					{
						status[cur.i][cur.j + 1] = 1;
						container.push(pair1(cur.i, cur.j + 1));
					}
				}
				if (cur.j + 1 < M&&cur.i - 1 >= 0 && land[cur.i - 1][cur.j + 1] == 'W')
				{
					if (status[cur.i - 1][cur.j + 1] == 0)
					{
						status[cur.i - 1][cur.j + 1] = 1;
						container.push(pair1(cur.i - 1, cur.j + 1));
					}
				}
			}
		}
	}
	cout << answer;
}