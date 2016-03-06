#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> greedy_Selector(vector<int>& start, vector<int>& fin)
{
	vector<int> solution;
	int n = start.size();
	int k = 0;
	solution.push_back(0);
	sort(fin.begin(), fin.end());
	for (int m = 1; m != n; ++m)
	{
		if (start.at(m) >= fin.at(k))
		{
			solution.push_back(m);
			k = m;
		}
	}
	return solution;
}

int main()
{
	vector<int> starting = { 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12 };
	vector<int> finishing = { 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16 };
	vector<int> solution = greedy_Selector(starting, finishing);
	for (auto i : solution)
		cout << i << '\n';
}