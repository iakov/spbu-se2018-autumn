#include <stdio.h>

int main( void )
{
    int count[28] = {0};

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
            {
                int id = i + j + k;

                count[id]++;
            }

    int tickets = 0;

    for (int i = 0; i < 28; i++)
        tickets += count[i] * count[i];

    printf("%d", tickets);

    return 0;
}
