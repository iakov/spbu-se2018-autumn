#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

extern void quickSort(int *numbers, int left, int right);


int transfer(char *param, int count)
{
	int sign = 1;
	int con = 0;
	while (param[count] != '\0')
	{
		if (param[count] == '-')
			sign = -1;
		else
		{
			con = 10 * con + (param[count] - '0');
		}
		count++;
	}
	con *= sign;
	return con;
}
void comfort(char *p, int *prm, int *check) {
	int count1 = 0;
	while (p[count1] != '\0') {
	
		if ((p[count1] >= '0') && (p[count1] <= '9') || ((p[count1] == '-') && (p[count1] >= '0') && (p[count1] <= '9')))  {
			*prm = transfer(p, count1);
			*check = 1;
			break;
		}
		count1++;
	}
}

int main(int argc, char *argv[]) {
	int i = 0, j = 0, tmp = 0, flag = 0, from = INT_MIN, to = INT_MAX, numbers, k = 0;
	int reduced[100], sorted[100];
	for (i = 1; i < argc; i++) {
		if (argv[i][2] == 'f') {
			comfort(argv[i], &from, &flag);
			if (flag == 0) {
				comfort(argv[i + 1], &from, &flag);
			}
			if (flag == 0) {
				comfort(argv[i + 2], &from, &flag);
			}
		}
		flag == 0;
		if (argv[i][2] == 't') {
			comfort(argv[i], &to, &flag);
			if (flag == 0) {
				comfort(argv[i + 1], &to, &flag);
			}
			if (flag == 0) {
				comfort(argv[i + 2], &to, &flag);
			}
	
		}
	}
	char space = ' ';
	while (space != '\n' && space != '\0') {
		scanf("%d%c", &numbers, &space);
		if (numbers > from && numbers < to) {
			reduced[k] = numbers;
			sorted[k] = numbers;
			k++;
		}
		if (numbers <= from) {
			printf("Stdout: ");
			fprintf(stdout, "%d \n", numbers);
		}
		if (numbers >= to) {
			printf("Stderr: ");
			fprintf(stderr, "%d \n", numbers);
		}
	}

	quickSort(sorted, 0, k - 1);
	printf("Sorted: ");
	for (i = 0; i < k; i++) {
		printf("%d ", sorted[i]);
	}
	int changes = 0;
	for (i = 0; i < k; i++) {
		if (sorted[i] != reduced[i]) changes++;
	}
	return changes;
}
