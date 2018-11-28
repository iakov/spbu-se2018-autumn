#include <stdio.h>
#include <math.h>

double sum_series(int n)
{
    double sum = 0;
    for (int i = n + 1; i <= 2 * n; i++)
    {
        sum += 1.0 / i;
    }
    return - sum - 1.0 / ((2 * n) * 2);
}

int main()
{
    int num;
    scanf("%d", &num);
    printf("%.20f %.20f\n", sum_series(num), sum_series(num) + log(2));
    return 0;
}
