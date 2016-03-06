#include <iostream>
using namespace std;
int N, K, R;
int Weight[100][10001];
struct edge
{
	int Length;
	int Cost;
	edge(){};
	edge(int L, int T) :Length(L), Cost(T){};
};
edge graph[100][100];
int solve(int a, int b)
{
	int curSolution = Weight[a][b];
	if (curSolution == 1 << 30)
	{
		for (unsigned i = 0; i != N; ++i)
		{
			if (i == a)
				continue;
			if (graph[a][i].Length == -1)
				continue;
			if (b - graph[a][i].Cost < 0)
				continue;
			int newSolution = solve(i, b - graph[a][i].Cost) + graph[a][i].Length;
			if (newSolution < curSolution)
			{
				Weight[a][b] = newSolution;
				curSolution = newSolution;
			}
		}
	}
	return curSolution;
}

int main(void)
{
	cin >> K >> N >> R;
	for (unsigned i = 0; i != N; ++i)
	{
		for (unsigned j = 0; j != N; ++j)
		{
			graph[i][j] = edge(-1, -1);
		}
	}
	for (unsigned i = 0; i != R; ++i)
	{
		int s, e, L, T;
		cin >> s >> e >> L >> T;
		graph[s][e].Length = L;
		graph[s][e].Cost = T;
	}
	for (unsigned i = 0; i != N; ++i)
	{
		for (unsigned j = 0; j <= K; ++j)
		{
			Weight[i][j] = 1 << 30;
		}
	}
	for (unsigned i = 0; i <= K; ++i)
	{
		Weight[N - 1][i] = 0;
	}
	int ans = solve(0, K);
	if (ans == 1 << 30)
		cout << -1 << endl;
	else
		cout << ans << endl;
}