#include <stdio.h>
#include <string.h>
#include <limits.h>

#define INF (int)1e9
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define WAITING 0
#define READ_FROM 3
#define READ_TO 4

extern int sort(int*, int);

_Bool check_int(char ch) {
 	return ch == '-' || (ch <= '9' && ch >= '0');
}

int my_atoi(char* str, int start_index) {
 	int num = 0;
	int i = start_index;
	int strsize = strlen(str);                      
	int sign = 1;
	if (str[i] == '-') {
		i++;
		sign = -1;
	}
	while (i < strsize && '0' <= str[i] && str[i] <= '9') {
	 	num = num * 10 + (int)(str[i] - '0');
		i++;
	}
	return sign * num;
}

int main(int argc, char* argv[]) {
	int from = INT_MIN;
	int to = INT_MAX;

	char params[50];
	for (int i = 1; i < argc; i++)
		strcat(params, argv[i]);

	int strsize = strlen(params);
	int i = 0;
	while (i < strsize) {
	 	while (i < strsize && params[i] != '=')
			i++;
		if (i >= strsize)
			break;
		if (params[i - 1] == 'm') // from 
		 	from = my_atoi(params, i + 1);
		if (params[i - 1] == 'o') // to
			to = my_atoi(params, i + 1);
		i++;
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
	//printf("\n%d", sort(array, size));
}
