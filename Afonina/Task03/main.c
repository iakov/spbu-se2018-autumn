#include <stdio.h>

long double sum_series(int n) {
    long double sum = -1;
    int cnt;
    for (int i = 2; i < 2 * n; i += 2, cnt = i) {
        sum += (long double)1 / (i * (i + 1));
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%.19Lf\n", sum_series(n));
}

