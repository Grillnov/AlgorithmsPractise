#include<stdio.h>

struct pair_p
{
	int* row;
	int* col;
	pair_p(int* row, int* col)
	{
		this->row = row;
		this->col = col;
	}
};

struct matrix_Dimension
{
	int row;
	int col;
	matrix_Dimension(int row = 0, int col = 0)
	{
		this->row = row;
		this->col = col;
	}
};

int min_Matrix_Chain_Aux(matrix_Dimension* mat_Info, int size, int* solution)
{
	if (solution[size] >= 0)
		return solution[size];
	int cost = 210000000;
	if (size == 1)
		cost = 0;
	else
	{
		for (int i = 1; i != size; ++i)
		{
			int sub_cost = min_Matrix_Chain_Aux(mat_Info, i, solution) + min_Matrix_Chain_Aux(mat_Info, size - i, solution) + mat_Info[0].row*mat_Info[i - 1].col*mat_Info[size - 1].col;
			if (cost > sub_cost)
				cost = sub_cost;
		}
	}
	solution[size] = cost;
	return cost;
}

int min_Matrix_Chain(matrix_Dimension* mat_Info, int size)
{
	int* solution = new int[size + 1];
	for (int i = 0; i != size + 1; ++i)
		solution[i] = -1;
	return min_Matrix_Chain_Aux(mat_Info, size, solution);
}

int min_Vio(matrix_Dimension* mat_Info, int size)
{
	int cost = 210000000;
	if (size == 1)
		return 0;
	else
	{
		for (int i = 1; i != size; ++i)
		{
			int sub_cost = min_Vio(mat_Info, i) + min_Vio(mat_Info, size - i) + mat_Info[0].row*mat_Info[i - 1].col*mat_Info[size - 1].col;
			if (cost > sub_cost)
				cost = sub_cost;
		}
	}
	return cost;
}

pair_p min_Solution(int* mat_Info, int size)
{
	int* m = new int[size*size];
	int* s = new int[(size - 1)*(size - 1)];
	for (int i = 0; i != size; ++i)
	{
		m[i*size + i] = 0;
	}
	for (int l = 2; l <= size; ++l)
	{
		for (int i = 0; i <= size - l; ++i)
		{
			int j = i + l - 1;
			m[i*size + j] = 210000000;
			for (int k = i; k != j; ++k)
			{
				int q = m[i*size + k] + m[(k + 1)*size + j] + mat_Info[i] * mat_Info[k + 1] * mat_Info[j + 1];
				if (q < m[i*size + j])
				{
					m[i*size + j] = q;
					s[i*(size - 1) + j - 1] = k;
				}
			}
		}
	}
	return pair_p(m, s);
}

void print_solution(int* solution, int i, int j, int size)
{
	if (i == j)
		printf("%s%d", "Mat", i);
	else
	{
		printf("%c", '(');
		print_solution(solution, i, solution[i*(size - 1) + j - 1], size);
		print_solution(solution, solution[i*(size - 1) + j - 1] + 1, j, size);
		printf("%c", ')');
	}
}

int main()
{
	matrix_Dimension matrices[4];
	matrices[0] = matrix_Dimension(10, 100);
	matrices[1] = matrix_Dimension(100, 5);
	matrices[2] = matrix_Dimension(5, 50);
	matrices[3] = matrix_Dimension(50, 20);
	int res = min_Matrix_Chain(matrices, 4);
	printf("%d", res);
	res = min_Vio(matrices, 4);
	printf("%c%d", '\n', res);
	int p[10] = { 10, 100, 5, 50, 20, 35, 50, 30, 10, 40 };
	pair_p s1 = min_Solution(p, 9);
	printf("%c%d", '\n', s1.row[8]);
	print_solution(s1.col, 0, 8, 9);
}