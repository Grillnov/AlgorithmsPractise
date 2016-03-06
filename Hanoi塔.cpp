#include <iostream>
using namespace std;

void Hanoi(int plates, int source, int intermediate, int destination)
{
	if (plates == 1)
	{
		cout << source << "->" << destination << endl;
		return;
	}
	Hanoi(plates - 1, source, destination, intermediate);
	cout << source << "->" << destination << endl;
	Hanoi(plates - 1, intermediate, source, destination);
}

int main(void)
{
	int plateN;
	cin >> plateN;
	Hanoi(plateN, 1, 2, 3);
}