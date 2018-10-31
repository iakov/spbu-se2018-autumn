#include<stdio.h>

long double sum_series(int N)
{
    long double res = (long double)0.0;
    long double j = (long double)N + 1.0;
    for (int i = N + 1; i <= 2 * N; i++)
    {
        res -= 1.0 / j;
        j = j + 1.0;
    }
    return res;

}

int main()
{
    int N;
    scanf("%d", &N);
    printf("%.18Lf \n", sum_series(N));
}
