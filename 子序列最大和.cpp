#include<stdio.h>
int find_MaxSubArray(int *Array, int* indices, int size)
{
	int sum = 0;
	int prev = 0;
	int index_L = 0;
	int index_R = 0;
	for (int i = 0; i != size - 1; i++)
	{
		for (int j = 1; j != size; j++)
		{
			for (int k = i; k <= j; k++)
			{
				sum += Array[k];
			}
			if (sum > prev)
			{
				index_L = i;
				index_R = j;
				prev = sum;
				sum = 0;
			}
			else
				sum = 0;
		}
	}
	indices[0] = index_L;
	indices[1] = index_R;
	return prev;
}
int main()
{
	int Arr[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, -15, -4, 7 };
	int con[2];
	int max_Sum = find_MaxSubArray(Arr, con, 16);
	printf("%d,%d,%d", max_Sum, con[0], con[1]);
}