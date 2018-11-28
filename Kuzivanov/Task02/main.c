#include <stdio.h>
#include <stdlib.h>

void my_sort(int*, int);

int main(int argc, char* argv[])
{
    char str[20000];
    gets(str);
    int a[100], b[100], n = 0, k = 0, i, j, to, from;
    _Bool b_to = 0, b_from = 0, first_to = 1, first_from = 1;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][2] == 'f')
        {
            for (j = 7; argv[i][j]; j++) k = k * 10 + argv[i][j] - '0';
            b_from = 1;
            from = k;
            k = 0;
        }
        else
        {
            for (j = 5; argv[i][j]; j++) k = k * 10 + argv[i][j] - '0';
            b_to = 1;
            to = k;
            k = 0;
        }
    }
    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
        {
            if (b_to && to <= k)
            {
                if (!first_to) fprintf(stderr, " ");
                first_to = 0;
                fprintf(stderr, "%i", k);
            }
            else if (b_from && from >= k)
            {
                if (!first_from) fprintf(stdout, " ");
                first_from = 0;
                fprintf(stdout, "%i", k);
            }
            else
            {
                a[n] = k;
                b[n] = k;
                n++;
            }
            k = 0;
        }
        else
        {
            k = k * 10 + str[i] - '0';
        }
        i++;
    }
    if (b_to && to <= k)
    {
        if (!first_to) fprintf(stderr, " ");
        first_to = 0;
        fprintf(stderr, "%i", k);
    }
    else if (b_from && from >= k)
    {
        if (!first_from) fprintf(stdout, " ");
        first_from = 0;
        fprintf(stdout, "%i", k);
    }
    else
    {
        a[n] = k;
        b[n] = k;
        n++;
    }
    //printf("\n");
    my_sort(a, n);
    int ans = 0;
    for (i = 0; i < n; i++)
    {
        if (a[i] != b[i]) ans++;
    }
    return ans;
}
