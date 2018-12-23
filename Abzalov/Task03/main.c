#include <stdio.h>
#include <stdlib.h>

typedef long double ld;

ld sum_series(int n) {
	ld res = 0.0;
	ld p = 2.0;
    for (int i = 1; i <= n; ++i)
        res += (ld)(1) / ((ld)(i) * p), p *= 2.0;
    return (-res);
}

int main() {
	int n;
    int check = scanf("%d", &n);
    if (check <= 0) {
		printf("Unexpected error!\n");
		fflush(stdin);
		exit(1);
	}
    printf("%.15Lf\n", sum_series(n));
    return 0;
}
