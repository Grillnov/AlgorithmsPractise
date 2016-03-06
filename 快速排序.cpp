#include<stdio.h>
#include<stdlib.h>
int Partition(int* Arr, int p, int r)
{
	int x = Arr[r];
	int i = p - 1;
	for (int j = p; j != r; j++)
	{
		if (Arr[j] >= x)
		{
			i++;
			int temp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = temp;
		}
	}
	int temp = Arr[i + 1];
	Arr[i + 1] = Arr[r];
	Arr[r] = temp;
	return i + 1;
}
int random_Partition(int* Arr, int p, int r)
{
	int piv = rand() % (r - p + 1) + p;
	int temp = Arr[r];
	Arr[r] = Arr[piv];
	Arr[piv] = temp;
	return Partition(Arr, p, r);
}
void quick_Sort(int* Arr, int p, int r)
{
	if (p < r)
	{
		int q = random_Partition(Arr, p, r);
		quick_Sort(Arr, p, q - 1);
		quick_Sort(Arr, q + 1, r);
	}
}
int main()
{
	int heap[10] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
	quick_Sort(heap, 0, 9);
	for (int i = 0; i != 10; i++)
	{
		printf("%d,", heap[i]);
		printf("%c,", '\b');
	}
}