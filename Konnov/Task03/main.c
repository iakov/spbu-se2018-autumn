#include <stdio.h>

int N;

double sum_series(int Num)
{
	int i;
	double retu = 0;
	for(i = 1; i <= Num; i++)
	{
		retu += -1 / (double) ((2 * i - 1) * 2 * i);
	}
	return retu;
}

double main()
{
	scanf("%d", &N);
	printf("%f", sum_series(N) );
	return sum_series(N);
}
