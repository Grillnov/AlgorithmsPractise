#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

fstream output("D:\\data.txt", ios::out);

bool is_Zero_vector(double* vec, unsigned n)
{
	bool ret = true;
	double max_diff = 0.0;
	for (int i = 0; i != n; ++i)
	{
		if (abs(vec[i]) > 1e-7)
			ret = false;
		if (abs(vec[i]) > max_diff)
			max_diff = abs(vec[i]);
	}
	printf("%1.7lf\n", max_diff);
	return ret;
}

double get1(double* x0)
{
	return x0[0] - pow(x0[1], 3) + 5 * pow(x0[1], 2) - 2 * x0[1] - 13;
}

double get2(double* x0)
{
	return x0[0] + pow(x0[1], 3) + pow(x0[1], 2) - 14 * x0[1] - 29;
}

bool is_Solved(double* x0)
{
	bool ret = true;
	double delta1 = get1(x0);
	double delta2 = get2(x0);
	if (abs(delta1) > 1e-7)
		ret = false;
	if (abs(delta2) > 1e-7)
		ret = false;
	return ret;
}

double get01(double* x)
{
	return x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5;
}

double get02(double* x)
{
	return x[0] + x[1] - 1;
}

double get03(double* x)
{
	return x[0] + x[2] - 3;
}

bool is_Solved0(double* x0)
{
	bool ret = true;
	double delta1 = get01(x0);
	double delta2 = get02(x0);
	double delta3 = get03(x0);
	if (abs(delta1) > 1e-7)
		ret = false;
	if (abs(delta2) > 1e-7)
		ret = false;
	if (abs(delta3) > 1e-7)
		ret = false;
	return ret;
}

int gauss(int n, double a[], double b[]) /*数组a、b对应于线性方程组AX=B中的向量A、B*/
{
	int i, j, k, *js, is;
	double max, t;
	js = (int*)malloc(n*sizeof(int)); /* 开辟用于记录列交换位置的动态空间 */
	for (k = 0; k<n - 1; k++)
	{
		max = 0.0;
		for (i = k; i<n; i++) /* 全选主元 */
		for (j = k; j<n; j++)
		{
			t = fabs(a[i*n + j]);
			if (t>max)
				max = t, js[k] = j, is = i;
		}
		if (max + 1.0 == 1.0) /* 如果系数矩阵奇异，就返回相关信息并退出 */
		{
			free(js);
			printf("\nHas not exclusive result or has not result!\n");
			return(0);
		}
		else
		{
			if (js[k] != k) /* 列交换 */
			for (i = 0; i<n; i++)
				t = a[i*n + k], a[i*n + k] = a[i*n + js[k]], a[i*n + js[k]] = t;
			if (is != k)
			{
				for (j = k; j<n; j++) /* 行交换 */
					t = a[k*n + j], a[k*n + j] = a[is*n + j], a[is*n + j] = t;
				t = b[k], b[k] = b[is], b[is] = t;
			}
		}
		max = a[k*n + k];
		for (j = k + 1; j<n; j++) /* 归一化 */
			a[k*n + j] /= max;
		b[k] /= max;
		for (i = k + 1; i<n; i++) /* 消元 */
		{
			for (j = k + 1; j<n; j++)
				a[i*n + j] -= a[i*n + k] * a[k*n + j];
			b[i] -= a[i*n + k] * b[k];
		}
	}
	max = a[(n - 1)*n + (n - 1)];
	if (fabs(max) + 1.0 == 1.0) /* 如果系数矩阵奇异，就返回相关信息并退出 */
	{
		free(js);
		printf("\nHas not exclusive result or has not result!\n");
		return(0);
	}
	b[n - 1] /= max; /* 以下为回代，而这一步计算向量的最后一个分量 */
	for (k = n - 2; k >= 0; k--)
	{
		t = 0.0;
		for (j = k + 1; j<n; j++)
			t += a[k*n + j] * b[j];
		b[k] -= t; /* 这时数组b用来记录解向量，而不是原来的常数向量 */
	}
	js[n - 1] = n - 1; /* 最后一步的系数矩阵的右下角(n-k+1)阶子阵只有一个元素a[n-1][n-1]，绝对值最大的当然是这个元素了 */
	for (k = n - 1; k >= 0; k--)
	if (js[k] != k)
		t = b[k], b[k] = b[js[k]], b[js[k]] = t;
	free(js);
	return(1);
}

void routine1()
{
	static unsigned counter = 0;
	double Jacobi[] =
	{
		1, -34,
		1, -6
	};
	double b[] =
	{
		-34,
		-10
	};
	double x0[] =
	{
		15,
		-2
	};
	while (!is_Solved(x0))
	{
		Jacobi[1] = -3 * pow(x0[1], 2) + 10 * x0[1] - 2;
		Jacobi[3] = 3 * pow(x0[1], 2) + 2 * x0[1] - 14;
		b[0] = -get1(x0);
		b[1] = -get2(x0);
		gauss(2, Jacobi, b);
		for (int i = 0; i != 2; ++i)
		{
			x0[i] += b[i];
		}
		printf("%f,%f\n", x0[0], x0[1]); ++counter;
	}
	printf("%d", counter);
}

void routine2()
{
	static unsigned counter = 0;
	double Jacobi[] =
	{
		-1, -1, -1,
		1, 1, 0,
		1, 0, 1
	};
	double b[] =
	{
		0,
		0,
		0
	};
	double x0[] =
	{
		(1 + sqrt(3)) / 2.0,
		(1-sqrt(3))/2.0,
		sqrt(3)
	};
	while (!is_Solved(x0))
	{
		Jacobi[0] = 2 * x0[0];
		Jacobi[1] = 2 * x0[1];
		Jacobi[2] = 2 * x0[2];
		b[0] = -get01(x0);
		b[1] = -get02(x0);
		b[2] = -get03(x0);
		gauss(3, Jacobi, b);
		for (int i = 0; i != 3; ++i)
		{
			x0[i] += b[i];
		}
		printf("%f,%f,%f\n", x0[0], x0[1], x0[2]); ++counter;
	}
}

int main(void)
{
	routine1();
}