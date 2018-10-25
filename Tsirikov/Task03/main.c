#include <stdio.h>
#include <stdlib.h>

long double sum_series(unsigned long long int N)
{
    long double result = 0;
    for (unsigned long long int i = 0; i < N; i++)
    {
        result -= 1.0 / (2 * i + 1) / (2 * i + 2);
    }
    return result;
}

long double main(int argc, char *argv[])
{
    unsigned long long int N = atoi(argv[1]);
    return sum_series(N);
}
