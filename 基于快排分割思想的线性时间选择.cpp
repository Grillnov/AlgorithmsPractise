#include<stdio.h>
int quick_Partition(int* Arr, int p, int q)
{
	int pivot = Arr[q];
	int i = p - 1;
	for (int j = p; j != q; j++)
	{
		if (Arr[j] <= pivot)
		{
			++i;
			int temp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = temp;
		}
	}
	int temp = Arr[i + 1];
	Arr[i + 1] = Arr[q];
	Arr[q] = temp;
	return i + 1;
}

int linear_Select(int *Arr, int Starting_Index, int Ending_Index, int Target_Index)
{
	while (Starting_Index != Ending_Index)
	{
		int index_Pivot = quick_Partition(Arr, Starting_Index, Ending_Index);
		int smaller_num = index_Pivot - Starting_Index + 1;
		if (Target_Index == smaller_num)
			return Arr[index_Pivot];
		else if (Target_Index < smaller_num)
		{
			Ending_Index = index_Pivot - 1;
		}
		else
		{
			Starting_Index = index_Pivot + 1;
			Target_Index = Target_Index - smaller_num;
		}
	}
	return Arr[Starting_Index];
}
int main()
{
	int Arr[3] = { 1, 2, 3 };
	int res = linear_Select(Arr, 0, 2, 3);
	printf("%d", res);
	return 0;
}