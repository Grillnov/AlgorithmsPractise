#include<stdio.h>

using namespace std;

struct goods
{
	int ID;
	int weight;
	int val;

	goods(int ID = 0, int weight = 0, int val = 0)
	{
		this->ID = ID;
		this->weight = weight;
		this->val = val;
	}
};

int max_Robbery(goods* List_of_Goods, int num_of_Goods, int total_Weight)
{
	int* solution = new int[(num_of_Goods + 1)*(total_Weight + 1)];
	for (int i = 0; i <= total_Weight; ++i)
	{
		solution[i] = 0;
	}
	for (int i = 0; i <= num_of_Goods; ++i)
	{
		solution[i*(total_Weight + 1)] = 0;
	}
	for (int i = 1; i <= num_of_Goods; ++i)
	{
		for (int j = List_of_Goods[i - 1].weight; j <= total_Weight; ++j)
		{
			int i_is_selected = solution[(i - 1)*(total_Weight + 1) + j - List_of_Goods[i - 1].weight] + List_of_Goods[i - 1].val;
			int i_not_selected = solution[(i - 1)*(total_Weight + 1) + j];
			solution[i*(total_Weight + 1) + j] = (i_is_selected > i_not_selected ? i_is_selected : i_not_selected);
		}
	}
	return solution[num_of_Goods*(total_Weight + 1) + total_Weight];
}

int main()
{
	goods Input[3];
	Input[0] = goods(1, 1, 35);
	Input[1] = goods(2, 1, 40);
	Input[2] = goods(3, 1, 45);
	int result = max_Robbery(Input, 3, 2);
	printf("%d", result);
}