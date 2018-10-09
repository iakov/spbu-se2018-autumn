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
	int from = INT_MIN;
	int to = INT_MAX;
	// what I was...
	/*for (int i = 1; i < argc; i++) {
		if (argv[i][1] == 'f')
			from = my_atoi(argv[i], 6);
		if (argv[i][1] == 't')
			to = my_atoi(argv[i], 4);
	}*/

	// what have I become...
	int status = WAITING;
	for (int i = 1; i < argc; i++) {
		int strsize = strlen(argv[i]);
	 	for (int strpnt = 0; strpnt < strsize; strpnt++) {   
			if (status != WAITING && check_int(argv[i][strpnt])) {
			 	if (status == READ_FROM)
					from = my_atoi(argv[i], strpnt);
				if (status == READ_TO)
					to = my_atoi(argv[i], strpnt);
				status = WAITING;
				break;
			}
			if (argv[i][strpnt] == 'f') {
				status = READ_FROM;
			}
			if (argv[i][strpnt] == 't') {
				status = READ_TO;
			}                                 
		}
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
