#include<stdio.h>
struct tri_int_tuple
{
	int integer1, integer2, integer3;
	tri_int_tuple(int i1, int i2, int i3)
	{
		integer1 = i1;
		integer2 = i2;
		integer3 = i3;
	}
};
tri_int_tuple maxi_Cross(int* Array, int low, int mid, int high)
{
	int left_sum = -2147463648;
	int right_sum = left_sum;
	int sum = 0;
	int max_left = 0;
	int max_right = 0;
	for (int i = mid; i != low - 1; i--)
	{
		sum += Array[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}
	sum = 0;
	for (int i = mid + 1; i != high + 1; i++)
	{
		sum += Array[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = i;
		}
	}
	return tri_int_tuple(max_left, max_right, left_sum + right_sum);
}
tri_int_tuple Maxi_SubArray(int* Array, int low, int high)
{
	if (high == low)
		return tri_int_tuple(low, high, Array[low]);
	else
	{
		int mid = (low + high) / 2;
		tri_int_tuple left_half = Maxi_SubArray(Array, low, mid);
		tri_int_tuple right_half = Maxi_SubArray(Array, mid + 1, high);
		tri_int_tuple cross_part = maxi_Cross(Array, low, mid, high);
		if (left_half.integer3 >= right_half.integer3&&left_half.integer3 >= cross_part.integer3)
			return left_half;
		else if (right_half.integer3 >= left_half.integer3&&right_half.integer3 >= cross_part.integer3)
			return right_half;
		else
			return cross_part;
	}
}
int main()
{
	int Arr[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, -15, -4, 7 };
	tri_int_tuple max_sub = Maxi_SubArray(Arr, 0, 15);
	printf("%d,%d,%d", max_sub.integer1, max_sub.integer2, max_sub.integer3);
}