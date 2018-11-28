#include <stdio.h>
#include <math.h>

 long double rowSum(int count){
     long double sum=0.0;
    for(int i=1; i<count;i++){
        sum-=1/(pow(2,i)*i);
    }
    return sum;

}
int main(){
    int n;
    scanf("%i",&n);
    printf("%.15Lf\n",rowSum(n));
    return 0;
}