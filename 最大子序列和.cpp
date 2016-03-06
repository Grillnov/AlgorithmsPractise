#include <iostream>
using namespace std;

int Solution(int *Arr, int size)
{
	int* solution = new int[size];
	int* endings = new int[size];
	solution[size - 1] = Arr[size - 1];
	for (int i = size - 2; i >= 0; --i)
	{
		int challengeVal = solution[i + 1];
		if (challengeVal > 0)
		{
			solution[i] = challengeVal + Arr[i];
			endings[i] = endings[i + 1];
		}
		else
		{
			solution[i] = Arr[i];
			endings[i] = i;
		}
	}
	int maxVal = 1 << 31;
	int ending = -1;
	int beginning = -1;
	for (int i = 0; i != size; ++i)
	{
		int curVal = solution[i];
		if (curVal > maxVal)
		{
			maxVal = curVal;
			beginning = i;
			ending = endings[i];
		}
	}
	cout << beginning << ',' << ending << endl;
	return maxVal;
}

int main(void)
{
	int Arr[] = { -2, 11, -4, 13, -5, -2 };
	cout << Solution(Arr, sizeof(Arr) / sizeof(int));
}