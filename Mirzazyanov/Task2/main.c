#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int main(int argc, char *argv[]) {
	int i = 0, j = 0, tmp = 0, flag = 0, from = -2147483647, to = 2147483647, numbers, k = 0;
	int reduced[100], sorted[100];
	for (i = 1; i < argc; i++) {
		if (argv[i][2] = 'f') {
			if (((argv[i][7] >= '0') && (argv[i][7] <= '9')) || (argv[i][7] == '-')) {
				from = transfer(argv[i], 7);
			}
			else if ((argv[i + 2][0] >= '0') && (argv[i + 2][0] <= '9') || (argv[i + 2][0] == '-')) {
				from = transfer(argv[i + 2], 0);
			}
			else if ((argv[i + 1][1] >= '0') && (argv[i + 1][1] <= '9') || (argv[i + 1][1] == '-')) {
				from = transfer(argv[i + 1], 1);
			}
			else from = transfer(argv[i + 1], 0);
			}
		if (argv[i][2] = 't') {
			if (((argv[i][5] >= '0') && (argv[i][5] <= '9')) || (argv[i][5] == '-')) {
				to = transfer(argv[i], 5);
			}
			else if ((argv[i + 2][0] >= '0') && (argv[i + 2][0] <= '9') || (argv[i + 2][0] == '-')) {
				to = transfer(argv[i + 2], 0);
			}
			else if ((argv[i + 1][1] >= '0') && (argv[i + 1][1] <= '9') || (argv[i + 1][1] == '-')) {
				to = transfer(argv[i + 1], 1);;
			}
			else to = transfer(argv[i + 1], 0);
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