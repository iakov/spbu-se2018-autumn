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
    return (-1) * ((sum1 + sum2) / 2.0);
    return sum;
}

int main (int argc, char *argv[]) {
    int n = atoi(argv[1]);
    printf("%.18f", sum_series (n));
    return 0;
}

