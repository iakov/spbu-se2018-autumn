#include <stdint.h>

double sum_series( int N )
{
	int64_t denumerator = N << 1;
	int64_t numerator = 2;

	double result = 0;
	while (N > 0)
	{
		result -= (double)numerator / (denumerator + 1);
		denumerator += numerator;
		N--;
	}

	return result;
}
