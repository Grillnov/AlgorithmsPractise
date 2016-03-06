#include<iostream>
int max(int para1, int para2)
{
	return (para1 > para2 ? para1 : para2);
}
int cut_Rod(int* price_Index, int inches)
{
	if (inches == 0)
		return 0;
	int q = -1;
	for (int i = 1; i <= inches; ++i)
		q = max(q, price_Index[i - 1] + cut_Rod(price_Index, inches - i));
	return q;
}
int main()
{
	int index[20] = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30, 36, 43, 57, 61, 67, 70, 73, 79, 83, 84 };
	std::cout << cut_Rod(index, 20);
	getchar();
}