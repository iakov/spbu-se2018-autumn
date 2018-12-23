#include <stdio.h>

long double sum_series(int n)
{
	long double Big = 1.0;
	for (int i = 1; i <= 20; ++i) Big *= 10.0;
	long double sum = 0.0, p = 2.0;
	for (int i = 1; i <= n; ++i)
	{
		sum += (long double)(Big) / ((long double)(i) * p);
		p *= 2.0;
	}
	return -(long double)(sum / Big);
}

int main()
{
	int n;
	scanf("%d", &n);
	long double result = sum_series(n);
	printf("%.49Lf\n", result);	
	return 0;
}
