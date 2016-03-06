#include<stdio.h>
//ÇÐÌú¹÷ÎÊÌâ
int* cut_Rod(int* price_Index, int total_Length)
{
	int* solution = new int[total_Length + 1];
	solution[0] = 0;
	for (int i = 1; i <= total_Length; ++i)
	{
		int q = -1;
		for (int j = 1; j <= i; ++j)
		{
			int trial_Solution = price_Index[j - 1] + solution[i - j];
			q = trial_Solution > q ? trial_Solution : q;
		}
		solution[i] = q;
	}
	return solution;
}

int main()
{
	int price_Index[4] = { 1, 5, 8, 9 };
	int* result = cut_Rod(price_Index, 4);
	printf("%d", result[4]);
}