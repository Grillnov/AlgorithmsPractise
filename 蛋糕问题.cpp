#include <iostream>
#include <math.h>

using namespace std;
int minVal = 1 << 30;
int currentVal = 0;
int* minV;
int* minA;
int N, M;

int maxVforMRH(int M, int R, int H)
{
	int v = 0;
	for (int i = 0; i != M; ++i)
	{
		v += (R - i)*(R - i)*(H - i);
	}
	return v;
}

void DFS(int H0, int R0, int Mc, int Nc)
{
	if (Mc == 0)
	{
		if (Nc != 0)
			return;
		else
		{
			minVal = minVal < currentVal ? minVal : currentVal;
			return;
		}
	}
	if (Nc <= 0)
		return;
	if (Nc < minV[Mc])
		return;
	if (currentVal + minA[Mc] >= minVal)
		return;
	if (H0 < Mc || R0 < Mc)
		return;
	if (Nc>maxVforMRH(Mc, R0, H0))
		return;
	for (int R = R0; R >= Mc; --R)
	{
		if (Mc == M)
			currentVal = R*R;
		for (int H = H0; H >= Mc; --H)
		{
			currentVal += 2 * R*H;
			DFS(H - 1, R - 1, Mc - 1, Nc - R*R*H);
			currentVal -= 2 * R*H;
		}
	}
}

int main(void)
{
	cin >> N >> M;
	minV = new int[M + 1];
	minA = new int[M + 1];
	minV[0] = 0;
	minA[0] = 0;
	for (int i = 1; i != M + 1; ++i)
	{
		minV[i] = minV[i - 1] + i*i*i;
		minA[i] = minA[i - 1] + 2 * i*i;
	}
	if (minV[M] > N)
	{
		cout << 0;
		return 0;
	}
	int maxH0 = (double)(N - minV[M - 1]) / (M*M) + 1;
	int maxR0 = sqrt(double(N - minV[M - 1])) / M + 1;
	currentVal = 0;
	DFS(maxH0, maxR0, M, N);
	if (minVal == 1 << 30)
		cout << 0;
	else
		cout << minVal;
}