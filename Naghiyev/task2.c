#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int num;
double sum;

double doubleSum()
{  double base= 0., sum[num] ; double final;
  sum [0]=0;
for (int i = 1; i <= num; i++)
{   base = (long double)(1/(pow(2,i)*i)) ;
    sum[i] = sum[i-1] + base ;
    sum[i] = sum[i];
  };  
    return sum[num]*-1;
}

int main() {
     double EXACT_SUM = ( double) -0.693147180559945309417;

    printf("Input number of series elements: ");
    scanf("%d", &num);

    printf("Exact sum: %.16lf \n", EXACT_SUM);
    printf("Double sum: %.16lf difference: %.16Lf \n", doubleSum(), doubleSum() - EXACT_SUM);
    
    int tuy;
    scanf("%d", &tuy);
    return 0;
}

