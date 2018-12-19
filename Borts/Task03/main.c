// -D__USE_MINGW_ANSI_STDIO
#include <stdio.h>
#include <math.h>

long double sum_series(int n);

void main()
{
	int N = 1;
	printf("Enter N: ");
	scanf("%d", &N);
	if(N < 1)
		printf("0.0");
	else
		printf("%.64Lf\n", -1*sum_series(N));
}

long double sum_series(int n)
{
	long double sum = 0.0;
	for(int i = 1; i <= n; ++i)
		sum += (1/(pow(2,i)*i));
	return sum;
}