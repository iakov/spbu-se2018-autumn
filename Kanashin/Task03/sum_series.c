#include <stdio.h>
#include <stdlib.h>

double sum_series(int n)
{
    double sum=0, znam;
    double k;
    for (int i=1; i<n+1;i++){
        k =(double)i;
        znam = 2.0*k*(2.0*k-1.0);
        sum -= 1.0/znam;
    }
    return sum;
}
