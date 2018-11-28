#include<stdio.h>

int main()
{
    int halfTicketCount[28];
    for (int j = 0; j < 28; j++)
            halfTicketCount[j] = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                halfTicketCount[i + j + k]++;
    int fullTicketCount = 0;
    for (int i = 0; i < 28; i++)
        fullTicketCount = fullTicketCount + halfTicketCount[i] * halfTicketCount[i];
    printf("%d \n", fullTicketCount); //considering that 000000 is a valid ticket number
    return 0;
}
