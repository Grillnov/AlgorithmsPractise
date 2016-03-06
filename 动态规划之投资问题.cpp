#include<stdio.h>
//投资问题
int max_Investment(int* Index, int num_of_items,int total_fund)
{
	int* solution = new int[(total_fund + 1)*(num_of_items + 1)];
	for (int i = 0; i <= total_fund; ++i)
	{
		solution[i] = 0;
	}
	for (int i = 0; i <= num_of_items; ++i)
	{
		solution[i*(total_fund + 1)] = 0;
	}
	
	for (int iter_Item = 1; iter_Item <= num_of_items; ++iter_Item)
	{
		for (int iter_Fund = 1; iter_Fund <= total_fund; ++iter_Fund)
		{
			for (int current_Fund = 0; current_Fund <= iter_Fund; ++current_Fund)
			{
				int current_Interest = solution[(iter_Item - 1)*(total_fund + 1) + iter_Fund - current_Fund] + Index[(iter_Item - 1)*(total_fund + 1) + current_Fund];
				if (current_Interest > solution[(iter_Item)*(total_fund + 1) + iter_Fund])
				{
					solution[(iter_Item)*(total_fund + 1) + iter_Fund] = current_Interest;
				}
			}
		}
	}

	int res = solution[(total_fund + 1)*num_of_items + total_fund];
	delete[] solution;
	return res;
}

int main()
{
	//int Index[] = { 0, 5, 15, 40, 80, 90, 95, 98, 100 ,  0, 5, 15, 40, 60, 70, 73, 74, 75 ,  0, 4, 26, 40, 45, 50, 51, 53, 53 };
	int Index[] = {0,20,50,65,80,85,85,0,20,40,50,55,60,65,0,25,60,85,100,110,115,0,25,40,50,60,65,70};
	printf("%d", max_Investment(Index, 4, 6));
}