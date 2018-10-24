#include <stdlib.h>

double sum_series( int N )
{
	int k = 2 * N;
	double result = 0;

	while (k > N)
	{
		result -= 1.0 / k;
		k--;
	}

	return result;
}
