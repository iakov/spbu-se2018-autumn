#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sum_series(int N)
{
	int i;
	N /= 2;
	double suma = 0;
	for(i = 0; i <= N - 1; i++)
	{
		suma -= (1.0 / (6 * N)) * (((double)N / (N + i)) + 4 * (1.0 / (1.0 + ((2 * i + 1.0) / (2 * N)))) + ((double)N / (N + i + 1)));
	}
	return suma;
}

int main()
{
	int Num; scanf("%d", &Num);
	double del = -log(2.0);
	printf("%.17lf \n%.17lf \n\n", sum_series(Num), sum_series(Num) - del);
	return 0;
}
