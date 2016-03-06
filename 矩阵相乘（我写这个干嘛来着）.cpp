#include<stdio.h>
void multiply_Matrix(int* mat1, int* mat2, int* matRes, int dimension)
{
	for (int i = 0; i != dimension; i++)
	{
		for (int j = 0; j != dimension; j++)
		{
			int Resij = 0;
			for (int k = 0; k != dimension; k++)
			{
				Resij += mat1[i*dimension + k] * mat2[k*dimension + j];
			}
			matRes[i*dimension + j] = Resij;
		}
	}
}
int main()
{
	int matrix1[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int matrix2[9] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int matResult[9];
	multiply_Matrix(matrix1, matrix2, matResult, 3);
	for (int i = 0; i != 9; i++)
		printf("%d,",matResult[i]);
}