#include <stdio.h>
#include <conio.h>

const int ten = 10, max = 28;
int main() {
	int count[max];
	for (int sum = 0; sum < max; sum++) {
		count[sum] = 0;
	}

		for (int first = 0; first < ten; first++) {
			for (int second = 0; second < ten; second++) {
				for (int third = 0; third < ten; third++) {
				count[first + second + third]++;
			}
		}
	}
		int result = 0;
		for (int last = 0; last < max; last++) {
			int current = count[last] * count[last];
			result = result + current;
		}
		printf("%d", result);
	_getch();
	return 0;
}
	
