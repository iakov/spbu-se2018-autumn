#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

extern int __sort(int counter, int massive[]);

int main(int argc, char *argv[])
{
    int down = INT_MIN, high = INT_MAX;
    for (int params = 1; params < (argc - 1); params += 3)
    {
        if (argv[params][2] == 'f')
        {
            down = atoi(argv[params + 2]);
        }
        else
        {
            high = atoi(argv[params + 2]);
        }
    }
    //reading parametrs
    int massive[100];
    for (int i=0; i < 100; i++)
    {
        massive[i] = 0;
    }
    //making massive
    int counter=0;
    while (scanf("%d", (massive + counter)) == 1)
    {
        if (massive[counter] <= down)
        {
            fprintf(stdout, "%d ", massive[counter]);
            massive[counter] = 0;
            counter--;
        }
        else if (massive[counter] >= high)
        {
            fprintf(stderr, "%d ", massive[counter]);
            massive[counter] = 0;
            counter--;
        }
        counter++;
    }
    //reading massive
    int counterOfTranspositions = __sort(counter, massive);
    //goto sort.s
    return counterOfTranspositions;
}
