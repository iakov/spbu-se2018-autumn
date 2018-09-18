#include <stdio.h>;
int main(){
  int a[28]={0};
  int count = 0, i;
  for (i = 0; i < 1000; i++){
     int j;
     j = (i % 10) + ((i / 10) % 10) + (i / 100);
     a[j]++;
  }
  for (i = 0; i < 28; i++) {
        count += a[i]*a[i];
  }
  printf("%d", count);
  return 0;
  }
