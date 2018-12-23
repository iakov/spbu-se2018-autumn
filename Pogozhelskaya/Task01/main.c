#include <stdio.h>

const int N = 10, MAX = 28;
int count[MAX], ans;

int main()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				count[i + j + k]++;
	for (int i = 0; i < MAX; i++)
		ans +=  count[i] * count[i];
	printf("%d\n", ans);
	return 0;
}