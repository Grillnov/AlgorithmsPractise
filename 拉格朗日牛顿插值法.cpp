#include<iostream>
#include<fstream>
#include<math.h>
using std::cout;
using std::fstream;
double Lagrange(double* x_grids, double* y_grids, unsigned n, double x)
{
	double result = 0.0f;
	for (unsigned register i = 0; i != n + 1; ++i)
	{
		double li = 1.0f;
		double xi = x_grids[i];
		for (unsigned register j = 0; j != n + 1; ++j)
		{
			if (j == i)
				continue;
			else
			{
				li *= (x - x_grids[j]);
				li /= (xi - x_grids[j]);
			}
		}
		result += y_grids[i] * li;
	}
	return result;
}

double linear(double* x_grids, double* y_grids, unsigned n, double x)
{
	int lower = 0;
	if (x < 0)
		lower = (int)x - 1;
	else
		lower = (int)x;
	double y1 = y_grids[lower + 5];
	double y2 = y_grids[lower + 6];
	return (y2 - y1)*(x - lower) + y1;
}

double H3(double* x_grids, double* y_grids, double* m_vals, unsigned n, double x)
{
	int lower = 0;
	if (x < 0)
		lower = (int)x - 1;
	else
		lower = (int)x;
	double y1 = y_grids[lower + 5];
	double y2 = y_grids[lower + 6];
	double m1 = m_vals[lower + 5];
	double m2 = m_vals[lower + 6];
	double result, ar, al, br, bl;
	result = 0.0f;
	al = (double)(1 + 2 * (x - lower))*(x - lower - 1)*(x - lower - 1);
	ar = (double)(1 - 2 * (x - lower - 1))*(x - lower)*(x - lower);
	bl = (double)(x - lower)*(x - lower - 1)*(x - lower - 1);
	br = (double)(x - lower - 1)*(x - lower)*(x - lower);
	result = y_grids[lower + 5] * al + y_grids[lower + 6] * ar + m_vals[lower + 5] * bl + m_vals[lower + 6] * br;
	return result;
}

double sample(double* x_grids, double* y_grids, double* m_vals, unsigned n, double x)
{
	int lower = 0;
	if (x < 0)
		lower = (int)x - 1;
	else
		lower = (int)x;
}

int main(void)
{
	fstream fout("D:\\res5.txt", std::ios::out);
	double xs[11], ys[11], ms[11];
	for (int i = 0; i != 11; ++i)
	{
		xs[i] = i - 5;
		ys[i] = (double)1 / (xs[i] * xs[i] + 1);
		ms[i] = -(double)(2 * xs[i]) / ((1 + xs[i] * xs[i])*(1 + xs[i] * xs[i]));
	}
	for (int i = 0; i != 1000; ++i)
	{
		double x = -5 + (double)i / 100;
		fout << x << ',' << H3(xs,ys,ms,11,x) << '\n';
	}
	fout.close();
	return 0;
}