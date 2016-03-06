#include<stdio.h>
void radix_Sort(int* Source, int *Target, int size)//default digit=3
{
	int digit[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int *Container = new int[size];
	for (int i = 0; i != size; i++)
	{
		int temp = (Source[i] - Source[i] / 100 * 100) % 10;
		Container[i] = temp;
	}
	for (int i = 0; i != size; i++)
	{
		digit[Container[i]] += 1;
	}
	for (int i = 1; i != 10; i++)
	{
		digit[i] += digit[i - 1];
	}
	for (int i = size - 1; i >= 0; i--)
	{
		Target[digit[Container[i]] - 1] = Source[i];
		--digit[Container[i]];
	}

	for (int i = 0; i != 10; i++)
		digit[i] = 0;

	for (int i = 0; i != size; i++)
	{
		int temp = (Target[i] - (Target[i] / 100 * 100)) / 10;
		Container[i] = temp;
	}
	for (int i = 0; i != size; i++)
	{
		digit[Container[i]] += 1;
	}
	for (int i = 1; i != 10; i++)
	{
		digit[i] += digit[i - 1];
	}
	for (int i = size - 1; i >= 0; i--)
	{
		Source[digit[Container[i]] - 1] = Target[i];
		--digit[Container[i]];
	}

	for (int i = 0; i != 10; i++)
		digit[i] = 0;

	for (int i = 0; i != size; i++)
	{
		int temp = Source[i] / 100;
		Container[i] = temp;
	}
	for (int i = 0; i != size; i++)
	{
		digit[Container[i]] += 1;
	}
	for (int i = 1; i != 10; i++)
	{
		digit[i] += digit[i - 1];
	}
	for (int i = size - 1; i >= 0; i--)
	{
		Target[digit[Container[i]] - 1] = Source[i];
		--digit[Container[i]];
	}
}
int main()
{
	int heap[10] = { 625, 761, 709, 246, 610, 197, 348, 916, 725, 153 };
	int Arr2[10];
	radix_Sort(heap, Arr2, 10);
	for (int i = 0; i != 10; i++)
	{
		printf("%d,", Arr2[i]);
	}
	return 0;
}