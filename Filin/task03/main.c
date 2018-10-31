#include <stdio.h>
#include <stdlib.h>

double sum_series(int n){
    double res = 0.0, lsum = 0.0, rsum = 0.0;
    n--;
    for(int i=n+1; i <= 2*n; i++) lsum = lsum - 1/(double)i;
    for(i=n; i <= 2*n-1; i++) rsum = rsum - 1/(double)i;
    res = (lsum*(2*n-1) + rsum*(2*n-2))/(4*n-3);
    return res;
}

int main(int argc, char*argv[]){
    int n;
    n = atoi(argv[1]);
    printf("%.20f\n", sum_series(n));
    return 0;
}
