#include<stdio.h>
void heapfy_Ai(int* heap, int i, int size)
{
	int index = i;
	while (1)
	{
		int largest = index;
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		if (left < size&&heap[index] < heap[left])
			largest = left;
		if (right < size&&heap[largest] < heap[right])
			largest = right;
		if (largest == index)
			break;
		else
		{
			int temp = heap[index];
			heap[index] = heap[largest];
			heap[largest] = temp;
			index = largest;
		}
	}
}
void build_Heap(int* heap, int size)
{
	for (int i = 0; i != size / 2; i++)
	{
		heapfy_Ai(heap, i, size);
	}
}
void sort_Heap(int* heap, int size)
{
	build_Heap(heap, size);
	for (int i = size - 1; i != 0; i--)
	{
		int temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;
		heapfy_Ai(heap, 0, i);
	}
}
class priority_Queue
{
	int *Heap;
	unsigned size;
public:
	priority_Queue(int* heap, unsigned size)
	{
		this->Heap = heap;
		this->size = size;
		build_Heap(Heap, size);
	}
	int extract_Max()
	{
		int return_Val = Heap[0];
		Heap[0] = Heap[this->size - 1];
		this->size--;
		heapfy_Ai(Heap, 0, this->size);
		return return_Val;
	}
	void heap_Increase(int i, int new_val)
	{
		this->Heap[i] = new_val;
		while (i > 0 && Heap[(i - 1) % 2] < Heap[i])
		{
			int temp = Heap[i];
			Heap[i] = Heap[(i - 1) % 2];
			Heap[(i - 1) % 2] = temp;
			i = (i - 1) % 2;
		}
	}
};
int main()
{
	int heap[10] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
	priority_Queue queue1 = priority_Queue(heap, 10);
	queue1.heap_Increase(2, 2);
	printf("%d,", queue1.extract_Max());
	printf("%d,", queue1.extract_Max());
	printf("%d,", queue1.extract_Max());
	printf("%d,", queue1.extract_Max());
	printf("%d,", queue1.extract_Max());
	return 0;
}