#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, digit_sum;
    int ticket_number = 0;
    int sums[28] = {0};

    for (i = 0; i <= 999; i++)
    {
        digit_sum = i % 10 + (i / 10) % 10 + (i / 100) % 10;
        sums[digit_sum] ++;
    }

    for (i = 0; i <= 27; i++)
    {
        ticket_number += sums[i] * sums[i];
    }

    printf("%d", ticket_number);
    return 0;
}
