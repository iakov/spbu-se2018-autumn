#include <stdio.h>

int N;

double sum_series(int Num)
{
	int i;
	double retu = 0.0;
	for(i = Num; i < 2 * Num; i++)
	{
		retu += -1.0 / (double)i;
	}
	return retu;
}

double main()
{
	scanf("%d", &N);
	printf("%.10lf", sum_series(N));
	return sum_series(N);
}
