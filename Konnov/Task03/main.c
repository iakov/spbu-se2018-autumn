#include <stdio.h>

int i, N;
double res;

float sum_series(int Num)
{
	double retu = 0;
	for(i = 1; i <= Num; i++)
	{
		retu += -1 / (double) ((2 * i - 1) * 2 * i);
	}
	return retu;
}

int main()
{
	scanf("%d", &N);
	printf("%f", sum_series(N));
	return 0;
}
