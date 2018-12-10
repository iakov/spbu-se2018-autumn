#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main( int argc, char** argv )
{
	int64_t min = INT64_MIN;
	int64_t max = INT64_MAX;

	int64_t for_sort[100];
	int64_t numbers[100];
	int64_t count = 0;

	for (int no = 1; no < argc; no++)
	{
		char* argument = argv[no];
		size_t length = strlen(argument);
		size_t eq;

		if (length > 4 && memcmp("--to", argument, 4) == 0)
		{
			for (eq = 4; eq < length && argument[eq] != '=';)
				eq++;
			max = atoi(argument + eq + 1);
		}
		else if (length > 6 && memcmp("--from", argument, 6) == 0)
		{
			for (eq = 6; eq < length && argument[eq] != '=';)
				eq++;
			min = atoi(argument + eq + 1);
		}
	}

	int state = 0;
	while (state == 0)
	{
		int number;

		scanf("%d", &number);
		if (number <= min)
		{
			fprintf(stdout, "%d ", number);
		}
		else if (number >= max)
		{
			fprintf(stderr, "%d ", number);
		}
		else
		{
			numbers[count] = number;
			for_sort[count] = number;
			count++;
		}

		if (getchar() != ' ')
			state = 1;
	}

	asm("push %rcx\n"
	    "push %rdx\n"
	    "lea  -1616(%rbp), %rcx\n"
	    "mov  -1648(%rbp), %rdx\n"
	    "call sort\n"
	    "pop %rdx\n"
	    "pop %rcx\n");

	int changes = 0;
	for (int no = 0; no < count; no++)
		if (numbers[no] != for_sort[no])
			changes++;

	return changes;
}
