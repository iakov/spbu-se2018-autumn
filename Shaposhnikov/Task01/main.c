#include <stdio.h>

int main()
    {
        int sum_cifres[28]={0},  i,  j,  k, num_lucky_tickets ;
        for (i=0;  i<10;  ++i)
            {
                for (j=0;  j<10; ++j)
                {
                    for (k=0;  k<10;  ++k)
                        {
                            ++sum_cifres[i+j+k];
                        }
                }
            }
        num_lucky_tickets = 0;
        for (i=0;  i<28;  ++i)
            {
                num_lucky_tickets += sum_cifres[i] * sum_cifres[i];
            }
        printf("%d", num_lucky_tickets);
        return 0;
    }
