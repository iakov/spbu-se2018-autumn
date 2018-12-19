#include <stdio.h>
#include <stdlib.h>

double sum_series(int n)
{
     double  pos_num = 0, neg_num = 0;
     int i;
  for (i = 1; i <= n; ++i)
  {
      if (i % 2 == 1)
        neg_num -=(double)1/i;
        else pos_num += (double)1/i;
  }
  return pos_num+neg_num;
}

int main(int argc, char *argv[])
 {
  int n;
  n = atoi(argv[1]);
  printf("%.17lf \n", sum_series(n));
  return 0;
}
