#include <stdio.h>

int main() 
{
    int equalDigitSums [28] = {0};

    for (int a = 0; a < 10; a++)
    {
        for (int b = 0; b < 10; b++)
        {
            for (int c = 0; c < 10; c++)
            {
                equalDigitSums[a + b + c]++;
            }
        }
    }

    int goldenTicketNumber = 0;

    for (int i = 0; i < 28; i++)
    {
        goldenTicketNumber += equalDigitSums[i] * equalDigitSums[i];
    }

    printf("Количество счастливых билетов: %d", goldenTicketNumber);

    return 0;
}
