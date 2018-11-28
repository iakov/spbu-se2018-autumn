#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double check (double result) {
    return fabs (result + log (2.0));
}

double sum_series (int n) {
    double sum = 0;
    --n;
    double sum1 = 0, sum2 = 0;
    for (int i = 1; i <= n; ++i) {
        sum1 += 1 / (double) (i + n);
    }
    for (int i = 0; i < n; i++) {
        sum2 += 1 / (double) (i + n);
    }
    return (-1) * ((sum1 * (2 * n - 1) + sum2 * (2 * n - 2)) / (4 * n - 3));
    //return (-1) * (sum1 + sum2) / 2.0;
    return sum;
}

int main (int argc, char *argv[]) {
    //int n = atoi(argv[1]);
    int n; scanf("%d", &n);
    double ans = 1, a, b;
    /*for (int i = 1; i <= 2 * n; ++i)
        for (int j = 1; j <= 2 * n; ++j)
        if (ans > check (sum_series(n, i, j))) {
            ans = check (sum_series(n, i, j));
            a = i; b = j;
        }*/
    printf("%.18Lf", check(sum_series (n)));
    return 0;
}

