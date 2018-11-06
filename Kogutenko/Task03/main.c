#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Error accounting at summing
long double two_sum(long double a, long double b, long double *error, bool plus) {
	long double x, y, av, bv, ar, br;
	x = a + b;
	bv = x - a;
	av = x - bv;
	br = b - bv;
	ar = a - av;
	y = ar + br;
	if(plus) {
		*error += y;
	} else {
		*error = y;
	}
	return x;
}

long double sum_series(long long n) {
	long double s1 = 0, s2 = 0, tmp1, tmp2, error = 0;
	long long i;
	for(i = 1; i <= n; i += 2) {
		tmp1 = (long double)1 / (long double)i;
		tmp2 = (long double)1 / (long double)tmp1;
		// Simple error accounting at division
		if(tmp2 != (long double)i) {
			s1 = two_sum(s1, (i - tmp2) / (long double)i, &error, true);
			s1 = two_sum(error, s1, &error, false);
		}
		s1 = two_sum(s1, tmp1, &error, true);
		s1 = two_sum(error, s1, &error, false);
	}
	for(i = 2; i <= n; i += 2) {
		tmp1 = (long double)1 / (long double)i;
		tmp2 = (long double)1 / (long double)tmp1;
		// Simple error accounting at division
		if(tmp2 != (long double)i) {
			s2 = two_sum(s2, (i - tmp2) / (long double)i, &error, true);
			s2 = two_sum(error, s2, &error, false);
		}
		s2 = two_sum(s2, tmp1, &error, true);
		s2 = two_sum(error, s2, &error, false);
	}
	return s2-s1;
}

int main(int argc, char **argv) {
	long double result = sum_series(atoll(argv[1]));
	printf("%.18Lf\n", result);
	return 0;
}
