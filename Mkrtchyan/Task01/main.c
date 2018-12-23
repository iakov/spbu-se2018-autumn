#include <stdio.h>

int main()
{
    int count[28];
    for(int i = 0; i < 28; ++i)
    {
        count[i] = 0;
    }
    for(int a = 0; a < 10; ++a)
    {
        for(int b = 0; b < 10; ++b)
        {
            for(int c = 0; c < 10; ++c)
            {
                ++ count[a + b + c];
            }
        }
    }
    int res = 0;
    for(int i = 0; i < 28; ++i)
    {
        res += count[i] * count[i];
    }
    printf("%d\n", res);
    return 0;
}
