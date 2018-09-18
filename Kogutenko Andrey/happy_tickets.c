#include <stdio.h>

char count[28]; // Array of quantities of bitwise sums

// Counting digits sum
short digit_sum(short n) {
	short s = n%10;
	n /= 10;
	s += n%10;
	n /= 10;
	s += n;
	return s;
}

int main() {
	short i;
	// Initializing with zeros
	for(i = 0; i <= 27; ++i) {
		count[i] = 0;
	}
	// Counting quantities of sums
	for(i = 0; i <= 999; ++i) {
		++count[digit_sum(i)];
	}
	int S = 0; // Quantity of happy tickets
	for(i = 0; i <= 27; ++i) {
		S += count[i]*count[i];
	}
	printf("%d\n", S);
	return 0;
}
