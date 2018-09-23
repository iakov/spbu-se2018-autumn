#include <stdio.h>

int main()
{
    int SumArray[28] = {0};
    int luckyTicketsCount = 0;
   
    for (int i = 0; i < 1000; i++) 
    {
        SumArray[i / 100 + (i / 10) % 10 + i % 10]++;
    }

    for (int i = 0; i < 28; i++) 
    {
        luckyTicketsCount += SumArray[i] * SumArray[i];
    }

    printf("%d\n", luckyTicketsCount);
    return 0;
}