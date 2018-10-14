#include <stdio.h>
#include <stdlib.h>

long double sum_series(int N)
{
    long double result = 0;
    for (int i=1; i <= N; i += 2)
    {
        result -= 1.0 / i;
    }
    for (int i=2; i <= N; i += 2)
    {
        result += 1.0 / i;
    }
    return result;
}

long double main(int argc, char *argv[])
{
    int N = atoi(argv[1]);
    return sum_series(N);
}
