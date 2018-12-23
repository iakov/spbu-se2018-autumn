#include <stdio.h>

const int MAX_SUM = 28;

int main() {
    int ans = 0;
    int numsum[MAX_SUM];
    for (int i = 0; i < MAX_SUM; i++) {
        numsum[i] = 0;
    }
    for (int i = 0; i < 1000; i++) {
        numsum[i / 100 + (i / 10) % 10 + i % 10]++;
    }
    for (int i = 0; i < MAX_SUM; i++) {
        ans += numsum[i] * numsum[i];
    }
    printf("%d\n", ans);
}