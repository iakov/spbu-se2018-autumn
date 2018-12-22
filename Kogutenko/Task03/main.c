#include <stdio.h>
#include <math.h>

typedef long long ll;
typedef long double ld;

ld sum_series1(ll n) {
	ld result = 0;
	ll i;
	for(i = 2; i <= n; i += 2) {
		result += (ld)1/(ld)i;
	}
	ld m = 0;
	for(i = 1; i <= n; i += 2) {
		m += (ld)1/(ld)i;
	}
	return result-m;
}

ld sum_series2(ll n) {
	ld result = 0;
	ll i;
	for(i = 0; i < n; i += 1) {
		result += (ld)1/((2*i + 1)*(2*i + 2));
	}
	return -result;
}

ld sum_series3(ll n) {
	ld result = 0;
	ll i;
	for(i = 0; i < n; i += 2) {
		result += (ld)1/((i+1)*(i+2));
	}
	ld m = 0;
	for(i = 1; i < n; i += 2) {
		m += (ld)1/((i+1)*(i+2));
	}
	return -(result-m+1)/2;
}

ld sum_series4(ll n) {
	ld result = 0;
	ll i;
	for(i = 1; i <= n; ++i) {
		result += (ld)1/(i*(4*i*i-1));
	}
	return -(result+1)/2;
}

ld sum_series5(ll n) {
	ld result = 0;
	ll i;
	for(i = 2; i <= n; i += 2) {
		result += (ld)1/(i*(4*i*i-1));
	}
	ld m = 0;
	for(i = 1; i <= n; i += 2) {
		m += (ld)1/(i*(4*i*i-1));
	}
	return -(result-m+1);
}

ld sum_series6(ll n) {
	ld result = 0;
	ll i;
	for(i = 2; i <= n; i += 2) {
		result += (ld)1/(i*(9*i*i-1));
	}
	ld m = 0;
	for(i = 1; i <= n; i += 2) {
		m += (ld)1/(i*(9*i*i-1));
	}
	return -(result-m + (ld)3/(ld)2)/2;
}

ld sum_series7(ll n) {
	ld result = 0;
	ll i;
	for(i = 1; i <= n; ++i) {
		result += (ld)1/(powl(2, i)*i);
	}
	return -result;
}

int main() {
	ll n;
	scanf("%lld", &n);
	printf("   %.35Lf\n", -logl(2));
	printf("1: %.35Lf\n", sum_series1(n));
	printf("2: %.35Lf\n", sum_series2(n));
	printf("3: %.35Lf\n", sum_series3(n));
	printf("4: %.35Lf\n", sum_series4(n));
	printf("5: %.35Lf\n", sum_series5(n));
	printf("6: %.35Lf\n", sum_series6(n));
	printf("7: %.35Lf\n", sum_series7(n));
	return 0;
}
