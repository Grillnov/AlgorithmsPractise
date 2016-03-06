#include<stdio.h>
//0-1±³°üÎÊÌâ
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
	int* solution = new int[total_Weight + 1];
	int* tracer = new int[(num_of_Goods + 1)*(total_Weight + 1)];
	for (int i = 0; i != total_Weight + 1; ++i)
		solution[i] = 0;
	for (int i = 1; i <= num_of_Goods; ++i)
	{
		for (int j = total_Weight; j >= List_of_Goods[i - 1].weight; --j)
		{
			int select = solution[j - List_of_Goods[i - 1].weight] + List_of_Goods[i - 1].val;
			if (select > solution[j])
			{
				solution[j] = select;
				tracer[i*(total_Weight + 1) + j] = 1;
			}
			else
			{
				tracer[i*(total_Weight + 1) + j] = 0;
			}
		}
	}

	int current_Weight = total_Weight;
	int current_Num = num_of_Goods;
	while (current_Num > 0)
	{

		if (tracer[current_Num*(total_Weight + 1) + current_Weight] == 1)
		{
			printf("%c,", List_of_Goods[current_Num - 1].ID);
			current_Weight -= List_of_Goods[current_Num - 1].weight;
		}
		--current_Num;
	}
	printf("\n");
	int result = solution[total_Weight];
	delete[] solution;
	delete[] tracer;
	return result;
}

int main()
{
	goods Input[6];
	Input[0] = goods('a', 10, 60);
	Input[1] = goods('b', 20, 100);
	Input[2] = goods('c', 30, 120);
	Input[3] = goods('d', 35, 135);
	Input[4] = goods('e', 40, 160);
	Input[5] = goods('f', 50, 190);
	int result = max_Robbery(Input, 6, 80);
	printf("%d", result);
}