#include<iostream>
inline int max(int para1, int para2)
{
	return (para1 >= para2 ? para1 : para2);
}

int base_cut_Rod(int* index_Price, int size)
{
	int* r = new int[size + 1];
	r[0] = 0;
	for (int j = 1; j <= size; ++j)
	{
		int q = -1;
		for (int i = 1; i <= j; ++i)
			q = max(q, index_Price[i - 1] + r[j - i]);
		r[j] = q;
	}
	return r[size];
}

int solution_cut_Rod(int* index_Price,int* r,int* s, int size)
{
	//int* r = new int[size + 1];
	r[0] = 0;
	//int* s = new int[size + 1];
	for (int j = 1; j <= size; ++j)
	{
		int q = -1;
		for (int i = 1; i <= j; ++i)
		{
			if (q < index_Price[i - 1] + r[j - i])
			{
				q = index_Price[i - 1] + r[j - i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	return r[size];
}

int main()
{
	int index[10] = { 1, 5, 8, 9, 10, 12, 13, 15, 16, 18 };
	int solution[11];
	int sub_cost[11];
	std::cout << solution_cut_Rod(index, sub_cost, solution, 10) << std::endl;
	int i = 10;
	while (i > 0)
	{
		std::cout << solution[i]<<' ';
		i = i - solution[i];
	}
	getchar();
}