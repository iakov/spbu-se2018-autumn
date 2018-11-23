#include <stdio.h>

int main()
{
	int count[28];
	int i;
	int summ = 0;
	for(i = 0; i < 28; i++)
	{	
		count[i] = 0;
	}
	for(i = 0; i < 1000; i++)
	{
		count[(i / 100) + (i % 100 % 10) + ((i / 10) % 10)]++;	
	}
	for(i = 0; i < 28; i++)
	{
		summ += count[i] * count[i];
	}
	printf("number of lucky tickets: %d", summ);
	return 0;
}
