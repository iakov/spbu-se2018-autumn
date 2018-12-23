#include <stdio.h>

long double raw_summing(int n) {
    long double ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1)
            ans -= 1.0 / (long double)i;
        else
            ans += 1.0 / (long double)i;
    }
    return ans;
}

long double two_summing(int n) {
    return (raw_summing(n / 2) * (n + 2) + raw_summing(n / 2 - 1) * (n)) / (2 * n + 2);
}

int main() {
    long double EXACT_VALUE = (long double)-0.69314718055994530941723212145817;
    int n;
    scanf("%d", &n);
    //printf("   EXACT VALUE: %.32Lf\n\n", EXACT_VALUE);
    printf("%.32Lf <-\n%.32Lf", EXACT_VALUE, two_summing(n)); 
    //check_main_solves(n);
}
