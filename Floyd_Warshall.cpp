#include <iostream>
#include <stack>

using namespace std;

void Floyd_Warshall(double* graph, unsigned verts)
{
	int *pred[2];
	double *len[2];
	for (unsigned i = 0; i != 2; ++i)
	{
		pred[i] = new int[verts*verts];
		len[i] = new double[verts*verts];
	}
	for (unsigned i = 0; i != verts; ++i)
	{
		for (unsigned j = 0; j != verts; ++j)
		{
			double Wij = graph[i*verts + j];
			len[0][i*verts + j] = Wij;
			if (Wij >= INFINITY)
			{
				pred[0][i*verts + j] = -1;
			}
			else
			{
				pred[0][i*verts + j] = i;
			}
			if (i == j)
			{
				pred[0][i*verts + j] = -1;
			}
		}
	}
	for (unsigned k = 0; k != verts; ++k)
	{
		for (unsigned i = 0; i != verts; ++i)
		{
			for (unsigned j = 0; j != verts; ++j)
			{
				double newDij = len[k % 2][i*verts + k] + len[k % 2][k*verts + j];
				double oldDij = len[k % 2][i*verts + j];
				if (newDij < oldDij)
				{
					len[(k + 1) % 2][i*verts + j] = newDij;
					pred[(k + 1) % 2][i*verts + j] = pred[k % 2][k*verts + j];
				}
				else
				{
					len[(k + 1) % 2][i*verts+j] = oldDij;
					pred[(k + 1) % 2][i*verts + j] = pred[k % 2][i*verts + j];
				}
			}
		}
	}

	for (unsigned i = 0; i != verts; ++i)
	{
		for (unsigned j = 0; j != verts; ++j)
		{
			cout << len[verts % 2][i*verts + j] << '\t';
		}
		cout << endl;
	}

	for (unsigned i = 0; i != verts; ++i)
	{
		for (unsigned j = 0; j != verts; ++j)
		{
			cout << i << "->" << j << ":\t";
			stack<int> Container;
			Container.push(j);
			int front = pred[verts % 2][i*verts + j];
			while (front != -1)
			{
				Container.push(front);
				front = pred[verts % 2][i*verts + front];
			}

			while (!Container.empty())
			{
				cout << Container.top() << " ";
				Container.pop();
			}
			cout << endl;
		}
	}

	delete[] pred[0];
	delete[] pred[1];
	delete[] len[0];
	delete[] len[1];
}

int main(void)
{
	double graph[] =
	{
		0, 3, 8, INFINITY, -4,
		INFINITY, 0, INFINITY, 1, 7,
		INFINITY, 4, 0, INFINITY, INFINITY,
		2, INFINITY, -5, 0, INFINITY,
		INFINITY, INFINITY, INFINITY, 6, 0
	};
	Floyd_Warshall(graph, 5);
}