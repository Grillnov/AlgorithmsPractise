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

void insertion_Sort(int* Arr, int Starting_Index, int Ending_Index)
{
	for (int j = Starting_Index + 1; j <= Ending_Index; j++)
	{
		int i = j - 1;
		int key = Arr[j];
		while (i > Starting_Index - 1 && key < Arr[i])
		{
			Arr[i + 1] = Arr[i];
			--i;
		}
		Arr[i + 1] = key;
	}
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

int search_Median(int *Arr, int Starting_Index, int Ending_Index)
{
	int num_of_Groups = (Ending_Index - Starting_Index + 1) / 5 + 1;
	for (int i = 1; i != num_of_Groups; i++)
	{
		insertion_Sort(Arr, Starting_Index + (i - 1) * 5, Starting_Index + i * 5 - 1);
	}
	insertion_Sort(Arr, Starting_Index + (num_of_Groups - 1) * 5, Ending_Index);
	int *medians = new int[num_of_Groups];
	for (int i = 1; i != num_of_Groups; i++)
	{
		medians[i - 1] = Arr[Starting_Index + 2 + (i - 1) * 5];
	}
	medians[num_of_Groups - 1] = Arr[(Ending_Index - (Starting_Index + (num_of_Groups - 1) * 5)) / 2 + (Starting_Index + (num_of_Groups - 1) * 5)];
	return linear_Select(medians, 0, num_of_Groups - 1, num_of_Groups / 2 + 1);
}

int quick_Partition_Another(int* Arr, int p, int q)
{
	int pivot = search_Median(Arr, p, q);
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

int linear_Select_Another(int *Arr, int Starting_Index, int Ending_Index, int Target_Index)
{
	while (Starting_Index != Ending_Index)
	{
		int index_Pivot = quick_Partition_Another(Arr, Starting_Index, Ending_Index);
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
	int Arr[5] = { 235, 212, 315, 567, 699 };
	printf("%d,", linear_Select_Another(Arr, 0, 4, 17));
	return 0;
}