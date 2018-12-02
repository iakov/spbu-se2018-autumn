#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

int *a, *b, n;
char *file_str;

void bubble_sort()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 1; j < n-i; j++)
        {
            if (strcmp(file_str + a[j], file_str + a[j-1]) < 0)
            {
                swap_in_array(j, j - 1, a);
            }
        }
    }
}

void insertion_sort()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i - 1; j >= 0 && strcmp(file_str + a[i], file_str + a[j]) < 0; j--) {}
        shift_in_array(j+1, i, a);
    }
}

void merge_sort(int l, int r)
{
    if (l == r-1) return;
    int m = (l + r) / 2, i = l, j = m, k;
    merge_sort(l, m);
    merge_sort(m, r);
    for (k = l; k < r; k++)
    {
        if (i == m || (j != r && strcmp(file_str + a[j], file_str + a[i]) < 0))
        {
            b[k] = a[j];
            j++;
        }
        else
        {
            b[k] = a[i];
            i++;
        }
    }
    for (k = l; k < r; k++) a[k] = b[k];
}

void quick_sort(int l, int r)
{
    if (l + 1 >= r) return;
    int mid = (2 * l + r - 1) / 3, i, j;
    i = l;
    j = r - 1;
    while (i != j)
    {
        while (i < j && strcmp(file_str + a[i], file_str + a[mid]) < 0) {i++;}
        while (i < j && strcmp(file_str + a[mid], file_str + a[j]) < 0) {j--;}
        swap_in_array(i, j, a);
        if (mid == i || mid == j) mid = i + j - mid;
        if (strcmp(file_str + a[i], file_str + a[j]) >= 0 && i < j) i++;
    }
    quick_sort(l, i);
    quick_sort(i + 1, r);
}

void radix_sort(int l, int r, int dig)
{
    if (l + 1 >= r) return;
    int d[257], i, j, k = l;
    for (i = 1; i < 257; i++) d[i] = 0;
    d[0] = l;
    for (i = l; i < r; i++)
    {
        d[file_str[a[i] + dig] + 1]++;
        b[i] = a[i];
    }
    for (i = 1; i < 257; i++) d[i] += d[i-1];
    for (i = 0; i < 257; i++)
    {
        for (j = l; j < r; j++)
        {
            if (file_str[b[j] + dig] == i)
            {
                a[k] = b[j];
                k++;
            }
        }
    }
    for (i = 1; i < 256; i++)
        radix_sort(d[i], d[i+1], dig+1);
}

int main(int argc, char *argv[])
{
    FILE *fin = fopen(argv[2], "r");
    int i, j;
    n = 0;
    for (i = 0; argv[1][i]; i++) n = n * 10 + argv[1][i] - '0';
    file_str = malloc(1000000000);
    a = malloc(4 * n + 4);
    a[0] = 0;
    char reading_str[10000];
    for (i = 0; i < n && fgets(reading_str, 10000, fin); i++)
    {
        for (j = 0; reading_str[j] != '\n' && reading_str[j]; j++) file_str[a[i] + j] = reading_str[j];
        file_str[a[i] + j] = '\0';
        a[i + 1] = a[i] + j + 1;
    }
    switch (argv[3][0])
    {
    case 'b': bubble_sort(); break;
    case 'i': insertion_sort(); break;
    case 'm':
        b = malloc(4 * n + 4);
        merge_sort(0, n);
        free(b);
        break;
    case 'q': quick_sort(0, n); break;
    case 'r':
        b = malloc(4 * n + 4);
        radix_sort(0, n, 0);
        free(b);
        break;
    default:
        printf("ERROR!!!\n");
        return 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = a[i]; file_str[j]; j++) printf("%c", file_str[j]);
        printf("\n");
    }
    free(a);
    free(file_str);
    fclose(fin);
}
