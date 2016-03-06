#include <iostream>
#include <queue>
using namespace std;
struct Vertex
{
	unsigned ID;
	double weight;
	Vertex(){};
	Vertex(unsigned I, double wei) :ID(I), weight(wei){};
};

bool operator<(const Vertex& lhs, const Vertex& rhs)
{
	return (lhs.weight < rhs.weight);
}

void BotchedDijkstra(double* graph, unsigned verts, unsigned source)
{
	double *distance = new double[verts];
	char *Status = new char[verts];
	for (int i = 0; i != verts; ++i)
	{
		distance[i] = INFINITY;
		Status[i] = 0;
	}
	distance[source] = 0.0;
	unsigned Cur = 0;
	for (int i = 0; i != verts; ++i)
	{
		for (int j = 0; j != verts; ++j)
		{
			if (Status[j] == 0)
			{
				Cur = j;
				break;
			}
		}
		for (int j = 0; j != verts; ++j)
		{
			if (Status[j] == 0)
			{
				if (distance[j] < distance[Cur])
				{
					Cur = j;
				}
			}
		}
		Status[Cur] = 1;
		for (int j = 0; j != verts; ++j)
		{
			double newLen = graph[Cur*verts + j] + distance[Cur];
			if (newLen < distance[j])
			{
				distance[j] = newLen;
			}
		}
	}
	for (int i = 0; i != verts; ++i)
	{
		cout << distance[i] << endl;
	}
}

int main()
{
	double Graph[] =
	{
		0, 10, 7, 2,
		INFINITY, 0, 2, INFINITY,
		INFINITY, INFINITY, 0, INFINITY,
		INFINITY, 3, 2, 0
	};
	Dijkstra(Graph, 4, 0);
}