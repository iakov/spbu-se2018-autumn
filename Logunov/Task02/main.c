#include <stdio.h>

#define INF (int)1e9

extern int sort(int*, int);

int my_atoi(char* str, int start_index) {
 	int num = 0;
	int i = start_index;
	int sign = 1;
	if (str[i] == '-') {
		i++;
		sign = -1;
	}
	while (str[i]) {
	 	num = num * 10 + (int)(str[i] - '0');
		i++;
	}
	return sign * num;
}

int main(int argc, char* argv[]) {
	int from = -INF;
	int to = INF;
	for (int i = 1; i < argc; i++) {
		if (argv[i][1] == 'f')
			from = my_atoi(argv[i], 6);
		if (argv[i][1] == 't')
			to = my_atoi(argv[i], 4);
	}
	int array[100];
	int size = 0, inp;
	while (scanf("%d", &inp)) {
		if (inp <= from) {
			fprintf(stdout, "%d ", inp);
			continue;
		}
		if (inp >= to) {
			fprintf(stderr, "%d ", inp);
			continue;
		}
	 	array[size] = inp;
		size++;
	}
	return sort(array, size);
	//printf("\n%d", sort(a, size));
}
