#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

extern int sort(int *arr, int size);

const int N = 100;

int from, to, lower_bound, upper_bound, n;

int main(int argc, char *argv[])
{
    int number;
    int *data = (int*)malloc(sizeof(int)*N); 
    int *buffer = (int*)malloc(sizeof(int)*N); 
    if (argc >= 2 && strcmp(argv[1], "--from") == 0 )
    {
	    from = atoi(argv[3]);
        lower_bound = 1;
    }
    else if (argc >= 2 && strcmp(argv[1], "--to") == 0 )
    {
	    to = atoi(argv[3]);
        upper_bound = 1;
    }
    if (argc >= 5 && strcmp(argv[4], "--to") == 0)
    {
        to = atoi(argv[6]);
        upper_bound = 1;
    }
    else if (argc >= 5 && strcmp(argv[4], "--from") == 0)
    {
        from = atoi(argv[6]);
        lower_bound = 1;
    }
    char temp;
    do { 
        scanf("%d%c", &number, &temp);
        if (lower_bound &&  (number <= from))
            fprintf(stdout, "%d ", number);
        else if (upper_bound && (number >= to))
            fprintf(stderr, "%d ", number);
        else
        {
            data[n] = number;
            buffer[n] = number;
            n++;
        }
    } while (temp != '\n');
    sort(data, n);
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        if (data[i] != buffer[i]) 
            cnt++;
    }
    free(data);
    free(buffer);
    printf("%d\n", cnt);
    return cnt;
}
