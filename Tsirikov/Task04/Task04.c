#include <stdio.h>

void other()
{
	printf("Exploit from input() is succesfully completed.\n");
}

void input()
{
	char str[31];
	printf("Ready to work. Write next line:\n");
	scanf("%s", str);
	printf("\"%s\" is entered. Normal ending.\n", str);
}

int main()
{
	input();
	return 0;
}
