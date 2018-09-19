#include <stdio.h>
int main()
{
    int arr[28];
    int i, j, k;
    for (i=0; i<28; i++)
    {
        arr[i]=0;
    };
    for (i=0; i<10; i++)
    {
        for (j=0; j<10; j++)
        {
            for (k=0; k<10; k++)
            {
                arr[i + j + k]++;
            };
        };
    };
    int answer=0;
    for (int i=0; i<28; i++)
    {
        answer += arr[i] * arr[i];
    };
    printf("%d", answer);
    return 0;
}
