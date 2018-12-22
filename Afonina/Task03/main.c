#include <stdio.h>

long double sum_series(int n) {
    long double sum = 0.0;
    for (int i = 2; i <= 2 * n; i += 2) {
        sum += (long double)1 / ((long double)i * (i + 1));
    }
    return sum - 1;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%.19Lf\n", sum_series(n));
}

