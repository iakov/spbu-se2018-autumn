#include <stdio.h>
#include <stdlib.h>


int main()
{
    int *arr = calloc( 28, sizeof( int ) );

    for( short i = 0; 10 > i; i++ )
    {
        for( short j = 0; 10 > j; j++ )
        {
            for( short k = 0; 10 > k; k++ )
            {
                arr[i + j + k]++;
            }
        }
    }

    int answer = 0;

    for( short i = 0; 28 > i; i++ )
    {
        answer += arr[i] * arr[i];
    }

    free( arr );
    printf( "%d\n", answer );
    return 0;
}
