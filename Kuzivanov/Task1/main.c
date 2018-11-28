#include <stdio.h>

int a[28];

int main()
{
    int i;
    for (i = 0; i < 1000; i++)
    {
        a[i/100+i/10%10+i%10]++;
    }
    int ans = 0;
    for (i = 0; i < 28; i++) ans += a[i]*a[i];
    printf("Answer = %d\n", ans);
}
