#include <stdio.h>

int main ()
{
    int mas[28], sum=0, i;

    for (i = 0; i <28; i++)
    mas[i]=0;

   for (i=0; i < 1000; i++)
   mas[i%10 + ((i/10) % 10) + i/100]++;


   for (i=0; i<28; i++) {
   	sum+= mas[i]*mas[i];
   }
   printf ("%d", sum);
   return 0;
}
