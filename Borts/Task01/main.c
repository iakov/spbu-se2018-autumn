#include <stdio.h>

int main()
{
	int LuckyResult = 0, ArrRes[28];
	for (int i = 0; i <= 27; i++)
	{
		ArrRes[i] = 0;
	}
	for (int i = 0; i <= 9; i++) 
		for (int j = 0; j <= 9; j++)
			for (int k = 0; k <= 9; k++) {
				ArrRes[i + j + k]++;
			}
	for (int i = 0; i <= 27; i++)
	{
		LuckyResult += (ArrRes[i] * ArrRes[i]);
	}

	printf("Count of LyckyTickets: %d\n", LuckyResult);

	return 0;
}