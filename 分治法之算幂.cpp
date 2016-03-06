#include<stdio.h>
unsigned long power_n(int power, int base)
{
	if (power == 0)
		return 1;
	if (power % 2 == 0)
	{
		int sqr = power_n(power / 2, base);
		return sqr*sqr;
	}
	else
	{
		int sqr = power_n((power - 1) / 2, base);
		return sqr*sqr*base;
	}
}

int main()
{
	printf("%d", power_n(13, 5));
}