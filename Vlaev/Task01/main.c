#include <stdio.h>
#include <string.h>

int main()
{
    int bilet_sums[28];
    memset(bilet_sums, 0, sizeof(bilet_sums));
    for (int a = 0; a < 10; a++)
        for (int b = 0; b < 10; b++)
            for (int c = 0; c < 10; c++)
                bilet_sums[a + b + c]++;
    long long int bilet_count = 0;
    for (int i = 0; i < 28; i++)
        bilet_count+=bilet_sums[i] * bilet_sums[i];
    printf("%lld",bilet_count);
    return 0;
}