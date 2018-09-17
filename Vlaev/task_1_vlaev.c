#include <stdio.h>
#include <string.h>

int main()
{
    int q[28];
    memset(q,0,sizeof(q));
    for (int a=0;a<10;a++)
        for (int b=0;b<10;b++)
            for (int c=0;c<10;c++)
                q[a+b+c]++;
    long long int sum=0;
    for (int i=0;i<28;i++)
        sum+=q[i]*q[i];
    printf("%lld",sum);
    return 0;
}
