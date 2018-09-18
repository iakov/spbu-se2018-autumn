#include <stdio.h>

int main() {
	int numsum[28];
	memset(numsum, (int)0, 28 * sizeof(int));
	for (int i = 0; i < 1000; i++) {
		numsum[i % 10 + (i / 10) % 10 + i / 100]++;
	}
	int ans = 0;
	for (int i = 0; i < 28; i++) {
		ans += numsum[i] * numsum[i];
	}
	printf("%d\n", ans);
	
	return 0;
}
