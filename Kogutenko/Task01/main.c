#include <stdio.h>
#include <string.h>

char count[28]; // Array of quantities of bitwise sums

// Counting digits sum
short digit_sum(short num) {
	short sum = num%10;
	num /= 10;
	sum += num%10;
	num /= 10;
	sum += num;
	return sum;
}

int main() {
	// Initializing with zeros
	memset(count, 0, 28);
	// Counting quantities of sums
	short i;
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
