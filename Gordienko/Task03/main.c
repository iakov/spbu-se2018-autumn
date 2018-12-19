#include <stdio.h>

double sum_series(int n)
{
    long long int divisor = 2, diff = 10;
    double result = 0;

    for (int i = 1; i <= n; i++)
    {
        result -= 1.0 / (double) divisor;
        divisor += diff;
        diff += 8;
    }

    return result;
}


int main()
{
    int n;
    scanf("%d", &n);
    printf("%.17f\n", sum_series(n));

    return 0;
}
