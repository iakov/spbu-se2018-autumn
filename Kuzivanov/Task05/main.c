#include <stdio.h>
#include <stdlib.h>

int *a, *b, n;
char *file_str;

void swap_array(int i, int j)
{
    int h = a[i];
    a[i] = a[j];
    a[j] = h;
}

void shift_array(int i, int j)
{
    int h = a[j], k;
    for (k = j; k > i; k--) a[k] = a[k-1];
    a[i] = h;
}

int compare_str(int i, int j) /// str[i] < str[j]
{
    int q;
    for (q = 0; file_str[a[i] + q] && file_str[a[j] + q] && file_str[a[i] + q] == file_str[a[j] + q]; q++) {}
    if (!file_str[a[j] + q]) return 0;
    if (!file_str[a[i] + q]) return 1;
    if (file_str[a[i] + q] < file_str[a[j] + q]) return 1;
    return 0;
}

void bubble_sort()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 1; j < n-i; j++)
        {
            if (compare_str(j, j - 1))
            {
                swap_array(j, j - 1);
            }
        }
    }
}

void insertion_sort()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i - 1; j >= 0 && compare_str(i, j); j--) {}
        shift_array(j+1, i);
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
        if (i == m || (j != r && compare_str(j, i)))
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
        while (i < j && compare_str(i, mid)) {i++;}
        while (i < j && compare_str(mid, j)) {j--;}
        swap_array(i, j);
        if (mid == i || mid == j) mid = i + j - mid;
        if (!compare_str(i, j) && i < j) i++;
    }
    quick_sort(l, i);
    quick_sort(i + 1, r);
}

void radix_sort(int l, int r, int dig)
{
    if (l + 1 >= r) return;
    int d[257], i, j, k = l, qq;
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
    char x[10000];
    for (i = 0; i < n && fgets(x, 10000, fin); i++)
    {
        for (j = 0; x[j] != '\n' && x[j]; j++) file_str[a[i] + j] = x[j];
        file_str[a[i] + j] = '\0';
        a[i + 1] = a[i] + j + 1;
    }
    if (argv[3][0] == 'b') bubble_sort();
    else if (argv[3][0] == 'i') insertion_sort();
    else if (argv[3][0] == 'm') {b = malloc(4 * n + 4); merge_sort(0, n); free(b);}
    else if (argv[3][0] == 'q') quick_sort(0, n);
    else if (argv[3][0] == 'r')
    {
        b = malloc(4 * n + 4);
        radix_sort(0, n, 0);
        free(b);
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
