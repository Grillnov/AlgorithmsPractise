#include <iostream>
#include <algorithm>
using namespace std;

unsigned getIndex(unsigned u, unsigned v, unsigned verts)
{
	return u*(2 * verts - 1 - u) / 2 + v - (u + 1);
}

inline int Comparison(const void* lhs, const void* rhs)
{
	double l = *reinterpret_cast<double*>(const_cast<void*>(lhs));
	double r = *reinterpret_cast<double*>(const_cast<void*>(rhs));
	return l > r;
}

double Kruskal(double* graph, unsigned verts, unsigned source)
{
	double *edgeTable = new double[verts*(verts - 1) / 2];
	for (unsigned i = 0; i != verts; ++i)
	{
		for (unsigned j = i + 1; j < verts; ++j)
		{
			edgeTable[getIndex(i, j, verts)] = graph[i*verts + j];
		}
	}
	qsort(reinterpret_cast<void*>(edgeTable), verts*(verts - 1) / 2, sizeof(double), Comparison);
	unsigned *pTree = new unsigned[verts];
	for (unsigned i = 0; i != verts; ++i)
	{
		pTree[i] = i;
	}
	unsigned edges = 0;
	double Res = 0.0;
	for (unsigned i = 0; i != verts; ++i)
	{
		for (unsigned j = i + 1; j < verts; ++j)
		{
			unsigned uTree = pTree[i];
			unsigned vTree = pTree[j];
			while (uTree != pTree[uTree])
			{
				uTree = pTree[uTree];
				pTree[uTree] = pTree[pTree[uTree]];
			}
			while (vTree != pTree[vTree])
			{
				vTree = pTree[vTree];
				pTree[vTree] = pTree[pTree[vTree]];
			}
			if (uTree != vTree)
			{
				++edges;
				pTree[uTree] = vTree;
				Res += edgeTable[getIndex(i, j, verts)];
				if (edges >= verts - 1)
					break;
			}
		}
	}
	return Res;
}

int main(void)
{
	/*double Graph[] =
	{
		0, 1, 2, 3,
		1, 0, 2, INFINITY,
		2, 2, 0, 15,
		3, INFINITY, 15, 0
	};*/
	double *Graph = new double[40 * 40];
	for (unsigned i = 0; i != 40 * 40; ++i)
	{
		Graph[i] = abs(static_cast<double>(rand())) / RAND_MAX;
	}
	cout << Kruskal(Graph, 40, 0) << endl;
}