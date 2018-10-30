#include <stdint.h>

double sum_series( int N )
{
	int64_t width = 1;
	while ((N >> width) > 0)
		width++;
	width--;

	int64_t count = 1 << width;
	int64_t denumerator = count << 1;
	int64_t numerator = 2;

	double result = 0;
	while (count > 0)
	{
		result -= (double)numerator / (denumerator + 1);
		denumerator += numerator;
		count--;
	}

	return result;
}
