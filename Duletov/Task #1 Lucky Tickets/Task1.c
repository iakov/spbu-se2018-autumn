#include <stdio.h>
#include <math.h>
int main()
{
    int i, tickets, sum, number, j;
    int Allsums[28];
        tickets=0;
        for ( i=0; i<28; i++)
    {
		Allsums[i]=0;
    }
    for ( i=0; i<1000; i++)
    {
        number=i;
        for ( j=0; j<3; j++)
        {
            sum+=(number%10);
            number=round(number/10);
        }
        Allsums[sum]+=1;
        sum=0;
    }
    for ( i=0; i<28; i++)
    {
        tickets+=Allsums[i]*Allsums[i];
    }
        printf("%d", tickets);
    return 0;
}
