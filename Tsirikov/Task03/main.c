#include <stdio.h>
#include <stdlib.h>

long double sum_series(unsigned long long int N)
{
    long double result = 0.0, half = 0.5;
    for (unsigned long long int i = 1; i <= N; i++)
    {
        result -= half / i;
	half /= 2.0;
    }
    return result;
}

long double main(int argc, char *argv[])
{
    unsigned long long int N = atoi(argv[1]);
    return sum_series(N);
}
