#include <stdio.h>

int main() {
    u_int equalSumArray[28] = {0};
    u_long luckyTicketsCount = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j< 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                equalSumArray[i + j + k]++;
            }
        }
    }

    for (int i = 0; i < 28; i++)
    {
        luckyTicketsCount += equalSumArray[i] * equalSumArray[i];
    }
    printf("the count of happy tickets is: %u", luckyTicketsCount);

    return 0;
}