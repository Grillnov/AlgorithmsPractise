#include<stdio.h>
void linear_Sort(int* Source, int* Target, int range, int size)
{
	int* Container = new int[range + 1];
	for (int i = 0; i <= range; i++)
	{
		Container[i] = 0;
	}
	for (int i = 0; i != size; i++)
	{
		++Container[Source[i]];
	}
	for (int i = 1; i <= range; i++)
	{
		Container[i] += Container[i - 1];
	}
	for (int i = size - 1; i >= 0; i--)
	{
		Target[Container[Source[i]] - 1] = Source[i];
		--Container[Source[i]];
	}
}
int main()
{
	int heap[10] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
	int Arr2[10];
	linear_Sort(heap, Arr2, 16, 10);
	for (int i = 0; i != 10; i++)
	{
		printf("%d,", Arr2[i]);
	}
	return 0;
}