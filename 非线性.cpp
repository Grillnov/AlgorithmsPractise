#include <stdio.h>
struct vec2
{
	double x1;
	double x2;
	vec2(double x1, double x2)
	{
		this->x1 = x1;
		this->x2 = x2;
	}
};

bool is_Zero(const vec2& v0)
{
	if (v0.x1 < 1e-8&&v0.x2 < 1e-8)
		return true;
	else
		return false;
}

double abs(double x)
{
	return x>0 ? x : -x;
}

bool is_Zero(double* Arr, int n)
{
	bool flag = true;
	for (int i = 0; i != n; ++i)
	{
		if (abs(Arr[i]) > 1e-8)
			flag = false;
	}
	return flag;
}

void Cal(vec2 x0)
{
	static unsigned counter = 0;
	while (!is_Zero(x0))
	{
		printf("%.12lf,%.12lf\n", x0.x1, x0.x2);
		vec2 d = vec2(-4 * x0.x1, -18 * x0.x2);
		vec2 g = vec2(4 * x0.x1, 18 * x0.x2);
		double alpha = (4 * x0.x1*g.x1 + 18 * x0.x2*g.x2) / (18 * (g.x2)*(g.x2) + 4 * (g.x1)*(g.x1));
		x0 = vec2(x0.x1 + alpha*d.x1, x0.x2 + alpha*d.x2);
		++counter;
	}
	printf("%d", counter);
}

void Cal2(vec2 x0)
{
	static unsigned counter = 0;
	while (!is_Zero(x0))
	{
		x0 = vec2(x0.x1 - (double)1.0 / 22.0 * 4 * x0.x1, x0.x2 - (double)1.0 / 22.0*18.0*x0.x2);
		printf("%f,%f\n", x0.x1, x0.x2);
		++counter;
	}
	printf("%d", counter);
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
		xpre[i] = 2;
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

	while (!is_Zero(rcur, n))
	{
		++k;
		/*if (k == n)
			break;*/
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
			printf("%f,", xpre[i]);
		}
		printf("\n");

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

	for (int i = 0; i != n; ++i)
	{
		printf("%f,", xpre[i]);
	}
	printf("\n");

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
	double Heissen[] =
	{
		2, -1,
		-1, 2
	};

	double b[] =
	{
		4, -2
	};

	Solving(Heissen, b, 2);
}