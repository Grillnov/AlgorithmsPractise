#include <iostream>
using namespace std;

int gcd(int a, int b)
{
	while (b != 0)
	{
		int temp = b;
		b = a%b;
		a = temp;
	}
	return a;
}

int main(void)
{
	cout << gcd(30, 36);
}