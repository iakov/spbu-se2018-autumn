#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//const double pi=-0.693147180559945309417;
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

int main(int argc, char* argv[])
{
    int n;
    n = atoi(argv[1]);
    printf("%.17f\n", sum_series(n));
    //printf("Accuracy: %.17f\n", fabs(sum_series(n)-pi));
    return 0;
}
