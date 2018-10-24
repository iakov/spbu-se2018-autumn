#include<stdio.h>

long double sum_series(int N)
{
    long double res = 0;
    for (int i = N + 1; i <= 2 * N; i++)
    {
        res = res + 1.0 / ((long double)i);
    }
    return -res;

}

int main()
{
    int N;
    scanf("%d", &N);
    printf("%Lf \n", sum_series(N));
}
