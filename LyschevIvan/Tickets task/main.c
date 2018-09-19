#include <stdio.h>

int main(){
    int counter[28];
    int i,sum=0;
    for(i=0;i<29;i++){ //Initializing
        counter[i]=0;
    }
    for(i=0;i<1000;i++){ // Counting amount of sums
        sum=i%10+i/100+(i/10%10);
        counter[sum]++;
        sum=0;
    }
    for(i=0;i<29;i++){ // Counting amount of possible combinations
        sum+=counter[i]*counter[i];
    }
    printf("%i",sum);

    return 0;
}