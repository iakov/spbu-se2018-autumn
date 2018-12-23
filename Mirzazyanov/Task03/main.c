#include<stdio.h>
#include<float.h>
#include<math.h>

double sum_series(int n) {
	long double numerator = -1, denominator = 1, z;
	int sign, d, i;
	for (i = 1; i < n; i++) {
		if (i % 2 == 1) {
			sign = 1;
		}
		else {
			sign = -1;
		}
		d = i + 1;
		numerator = numerator * d + sign * denominator;
		denominator = denominator * d;
		//док-во по индукции n(n+1) < dbl_max;
		if (denominator > (DBL_MAX / (d + 1))) {
			z = denominator / (d + 1);
			numerator /= z;
			denominator /= z;
		}
	}
	return 1.0 * numerator / denominator;
}
int main() {
	int n, res;
	double a = 3.162;
	scanf("%d", &n);
	printf("%.16f\n", sum_series(n));
}