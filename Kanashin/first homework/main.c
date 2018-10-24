#include <stdio.h>


int main()
{
    int countsum[28];
    int i, sumnum, counttick = 0, num;
    for (i=1; i<28; i++){
        countsum[i]=0;
    }
    for (i=1; i<1000; i++)
    {
        sumnum = 0;
        num = i;
        while (num>0)
        {
            sumnum += num % 10;
            num /= 10;
        }
        countsum[sumnum]++;
    }
    for (i=1; i<28; i++)
    {
        counttick += countsum[i]*countsum[i];
    }
    printf("%d ", counttick);
    return 0;
}
