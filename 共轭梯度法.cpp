#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

fstream output("D:\\data.txt", ios::out);

inline double getFunVal(int i,int j)
{
	double x_fac = ((double)1.0 / 20)*i;
	double y_fac = ((double)1.0 / 20)*j;
	return sin(x_fac*y_fac);
}

inline double getBorderVal(int i, int j)
{
	double x_fac = ((double)1.0 / 20)*i;
	double y_fac = ((double)1.0 / 20)*j;
	return x_fac*x_fac + y_fac*y_fac;
}

bool is_Zero_vector(double* vec, unsigned n)
{
	bool ret = true;
	double max_diff = 0.0;
	for (int i = 0; i != n; ++i)
	{
		if (vec[i] != 0)
			ret = false;
		if (abs(vec[i] > max_diff))
			max_diff = vec[i];
	}
	printf("%1.6f\t", max_diff);
	return ret;
}

double* Solving(double* mat, double* b, unsigned n)
{
	int k = 0;
	double* xpre = new double[n];
	double* xcur = new double[n];
	double* rpre = new double[n];
	double* rcur = new double[n];
	double* rnext = new double[n];
	double* pcur = new double[n];
	double* ppre = new double[n];

	for (int i = 0; i != n; ++i)
	{
		xpre[i] = 0;
	}

	for (int i = 0; i != n; ++i)
	{
		double Ax0i = 0.0f;
		for (int j = 0; j != n; ++j)
		{
			Ax0i += mat[i*n + j] * xpre[j];
		}
		rcur[i] = b[i] - Ax0i;
	}

	while (!is_Zero_vector(rcur, n))
	{
		++k;
		if (k == n)
			break;
		if (1 == k)
		{
			for (int i = 0; i != n; ++i)
			{
				pcur[i] = rcur[i];
			}
		}
		else
		{
			double upper = 0.0, lower = 0.0;
			for (int i = 0; i != n; ++i)
			{
				upper += rcur[i] * rcur[i];
				lower += rpre[i] * rpre[i];
			}
			double beta = upper / lower;

			for (int i = 0; i != n; ++i)
			{
				pcur[i] = ppre[i] * beta + rcur[i];
			}
		}

		double upper = 0.0, lower = 0.0;
		for (int i = 0; i != n; ++i)
		{
			upper += rcur[i] * rcur[i];
			double item = 0.0;
			for (int j = 0; j != n; ++j)
			{
				item += mat[i*n + j] * pcur[j];
			}
			lower += item*pcur[i];
		}
		double alpha = upper / lower;

		for (int i = 0; i != n; ++i)
		{
			xcur[i] = xpre[i] + alpha*pcur[i];
		}

		for (int i = 0; i != n; ++i)
		{
			double item = 0.0;
			for (int j = 0; j != n; ++j)
			{
				item += mat[i*n + j] * pcur[j];
			}
			rnext[i] = rcur[i] - alpha*item;
		}

		double* temp = xpre;
		xpre = xcur;
		xcur = temp;

		temp = ppre;
		ppre = pcur;
		pcur = temp;

		temp = rpre;
		rpre = rcur;
		rcur = rnext;
		rnext = temp;
	}

	delete[] rpre;
	delete[] rcur;
	delete[] rnext;
	delete[] ppre;
	delete[] pcur;
	delete[] xcur;

	return xpre;
}

int main(void)
{
	output << setprecision(4);

	double* mat = new double[(19 * 19 * 19 * 19)];
	double b[19 * 19];
	double fac1 = 1 + ((double)1 / 20)*((double)1 / 20);
	double fac2 = -(double)1 / 4;
	double h = (double)1 / 20;

	for (int i = 0; i != (19 * 19 * 19 * 19); ++i)
	{
		mat[i] = 0.0;
	}

	for (int i = 0; i != 19 * 19; ++i)
	{
		mat[i * 361 + i] = fac1;
	}

	for (int i = 0; i != 361 - 1; ++i)
	{
		mat[i * 361 + i + 1] = fac2;
		mat[(i + 1) * 361 + i] = fac2;
	}

	for (int i = 0; i != 361 - 19; ++i)
	{
		mat[i * 361 + i + 19] = fac2;
		mat[(i + 19) * 361 + i] = fac2;
	}

	for (int i = 0; i != 19; ++i)
	{
		for (int j = 0; j != 19; ++j)
		{
			double current_fact = h*h / 4 * getFunVal(i + 1, j + 1);
			if (i == 0||i==18)
			{
				current_fact += (double)1 / 4 * getBorderVal(i, j + 1);
				if (j == 0 || j == 18)
				{
					current_fact += double(1) / 4 * getBorderVal(i + 1, j);
				}
			}
			b[i * 19 + j] = current_fact;
		}
	}

	double* res = Solving(mat, b, 361);
	for (int i = 0; i != 20; ++i)
	{
		for (int j = 0; j != 20; j++)
		{
			if (i == 0 || j == 0)
				output << getBorderVal(i, j)<<'\t';
			else
				output << res[(i - 1) * 19 + j - 1]<<'\t';
		}
		output << '\n';
	}

	output.close();
}