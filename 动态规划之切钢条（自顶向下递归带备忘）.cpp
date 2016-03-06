#include<iostream>
int max(int para1, int para2)
{
	return (para1 >= para2 ? para1 : para2);
}

int memorized_cut_Rod_aux(int* p, int size, int* r)
{
	int q = 0;
	if (r[size] >= 0)
		return r[size];
	if (size == 0)
		q = 0;
	else
	{
		q = -1;
		for (int i = 1; i <= size; ++i)
			q = max(q, p[i - 1] + memorized_cut_Rod_aux(p, size - i, r));
	}
	r[size] = q;
	return q;
}

int memorized_cut_Rod(int* price_Index, int size)
{
	int* r = new int[size + 1];
	for (int i = 0; i <= size; ++i)
		r[i] = -1;
	return memorized_cut_Rod_aux(price_Index, size, r);
}

int main()
{
	int index[10] = { 4, 5, 8, 9, 10, 12, 13, 15, 16, 18 };
	std::cout << memorized_cut_Rod(index, 10);
	getchar();
}