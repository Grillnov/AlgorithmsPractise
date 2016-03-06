#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	int length, cases;
	scanf("%d%d", &length, &cases);
	char** strlist = new char*[cases];
	int* inversed_pairs = new int[cases];
	for (int i = 0; i != cases; ++i)
	{
		strlist[i] = new char[length];
		scanf("%s", strlist[i]);
	}
	for (int i = 0; i != cases; ++i)
	{
		int inversed = 0;
		for (int j = 0; j != length - 1; ++j)
		{
			for (int k = j + 1; k != length; ++k)
			{
				if (strlist[i][j] > strlist[i][k])
					++inversed;
			}
		}
		inversed_pairs[i] = inversed;
	}
	for (int j = 0; j < cases - 1; j++)
	{
		for (int i = 0; i<cases - 1 - j; i++)
		{
			if (inversed_pairs[i]>inversed_pairs[i + 1])
			{
				int temp = inversed_pairs[i];
				inversed_pairs[i] = inversed_pairs[i + 1];
				inversed_pairs[i + 1] = temp;
				char* tempp = strlist[i];
				strlist[i] = strlist[i + 1];
				strlist[i + 1] = tempp;
			}
		}
	}
	for (int i = 0; i != cases; ++i)
	{
		printf("%s\n", strlist[i]);
	}
}