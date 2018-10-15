#include <stdio.h>
int main(){
 int sum[28];
 for(int i = 0; i < 28; ++i)
  sum[i] = 0;
 for(int a = 0; a < 10; ++a){
  for(int b = 0; b < 10; ++b){
   for(int c = 0; c < 10; ++c){
   ++sum[a+b+c];
   }
  } 
 }
 int qant = 0;
 for(int i = 0; i < 28; ++i)
  qant += sum[i] * sum[i];
 printf("%d", qant);
 return 0;
}
