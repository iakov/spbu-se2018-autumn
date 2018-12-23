#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define startn 200
#define startlen 10

char **strings;
long long int  *lengths;
long long int  n = 0;
//used to compare strings with different lengths
char get_ith_symbol(char* a,long long int  len ,long long int  i)
{
    if (i>=len)
    {
        return 0;
    }
    else return a[i];
}

//swapping strings and their lengths
void swap(long long int  index1, long long int  index2)
{
    char* temp = strings[index1];
    strings[index1] = strings[index2];
    strings[index2] = temp;
    long long int  temp_len=lengths[index1];
    lengths[index1]=lengths[index2];
    lengths[index2]=temp_len;
}
// strlen is not viable,because unused memory is malloced, so it doesnt work properly
// hence cmp is used
char cmp(char* a, char* b,long long int  len_a,long long int  len_b)
{
    for (long long int  i = 0; i < max(len_a,len_b); i++)
    {
        if (get_ith_symbol(a,len_a,i) > get_ith_symbol(b,len_b,i))
        {
        return 1;
        }
        if (get_ith_symbol(b,len_b,i) > get_ith_symbol(a,len_a,i))
        {
        return 0;
        }
    }
    return 1;
}

void bubbleSort(long long int  n)
{
    long long int  n1 = n - 1;
    bool swapped;
    do
    {
        swapped = 0;
        for (long long int  i = 0; i < n1; i++)
        {
            if (cmp(strings[i],strings[i+1],lengths[i],lengths[ i + 1]))
            {
                swap(i, i + 1);
                swapped = 1;
            }
        }
        n1--;
    }
    while (swapped);
}

void insertionSort(long long int  n)
{
    long long int  i = 1;
    while (i < n)
    {
        long long int  j = i;
        while ((j > 0) &&
              (1-cmp(strings[j],strings[j-1],lengths[j],lengths[ j - 1])))
        {
            swap(j, j - 1);
            j = j - 1;
        }
        i += 1;
    }

}

long long int  partition(long long int  low, long long int  high)
{
    long long int  pivot = high;    // pivot
    long long int  i = (low - 1);  // Index of smaller element

    for (long long int  j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (cmp(strings[pivot],strings[j],lengths[pivot],lengths[j]))
        {
            i++;
            swap(i, j);
            // increment index of smaller element
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

void startQuickSort(long long int  low, long long int  high)
{
    if (low < high)
    {

        long long int  pi = partition(low, high);

        // Separately sort elements before
        // partition and after partition
        startQuickSort(low, pi - 1);
        startQuickSort(pi + 1, high);
    }
}

void quickSort(long long int  low, long long int  high)
{
    startQuickSort(low, high);
}

void merge(long long int  l, long long int  m, long long int  r)
{
    long long int  i, j, k;
    long long int  n1 = m - l + 1;
    long long int  n2 = r - m;


    char** L=malloc(n1*sizeof(char*));
    if (L==NULL)
    {
        printf("Memory allocation error!");
        free(lengths);
        for (i=0;i<n;i++)
        {
            free(strings[i]);
        }
        free(strings);
        exit(4);
    }
    char** R=malloc(n2*sizeof(char*));
    if (R==NULL)
    {
        printf("Memory allocation error!");
        free(lengths);
        for (i=0;i<n;i++)
        {
            free(strings[i]);
        }
        free(strings);
        exit(4);
    }
    long long int * len1=malloc(n1*sizeof(long long int ));
    long long int * len2=malloc(n2*sizeof(long long int ));
    if (len1==NULL || len2==NULL)
    {
        printf("Memory allocation error!");
        free(lengths);
        for (i=0;i<n;i++)
        {
            free(strings[i]);
        }
        free(strings);
        exit(4);
    }

    for (i = 0; i < n1; i++)
    {
        L[i] = strings[l + i];
        len1[i]=lengths[l+i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = strings[m + 1 + j];
        len2[j]=lengths[m+1+j];
    }


    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (cmp(R[j],L[i],len2[j],len1[i]))
        {
            strings[k] = L[i];
            lengths[k]=len1[i];
            i++;
        }
        else
        {
            strings[k] = R[j];
            lengths[k]=len2[j];
            j++;
        }
        k++;
    }


    while (i < n1)
    {
        strings[k] = L[i];
        lengths[k]=len1[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        strings[k] = R[j];
        lengths[k]=len2[j];
        j++;
        k++;
    }
    free(L);
    free(R);
    free(len1);
    free(len2);
}

void startMergeSort( long long int  l, long long int  r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
       long long int  m = l + (r - l) / 2;

        // Sort first and second halves
        startMergeSort(l, m);
        startMergeSort(m + 1, r);

        merge(l, m, r);
    }
}


void mergeSort(long long int  l, long long int  r)
{
    startMergeSort(l, r);
}

// A function to do counting sort of strings[] according to
// the digit represented by exp.
void countSort(long long int  n, long long int  num)
{
    char** output; // output stringsay
    output=malloc(sizeof(char*)*n);
    if (output==NULL)
    {
        printf("Memory allocation error!");
        free(lengths);
        for (long long int  i=0;i<n;i++)
        {
            free(strings[i]);
        }
        free(strings);
        exit(4);
    }
    long long int  i, count[256] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
    {
        count[(long long int )get_ith_symbol(strings[i],lengths[i],num)]++;
    }
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 256; i++)
    {
        count[i] += count[i - 1];
    }
    long long int * lens=malloc(n*sizeof(long long int ));
    if (lens==NULL)
    {
        printf("Memory allocation error!");
        free(lengths);
        for (i=0;i<n;i++)
        {
            free(strings[i]);
        }
        free(strings);
        exit(4);
    }
    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        long long int  index=get_ith_symbol(strings[i],lengths[i],num);
        output[count[index] - 1] = strings[i];
        (lens[count[index]-1])=lengths[i];
        count[(long long int )get_ith_symbol(strings[i],lengths[i],num)]--;
    }

    // Copy the output array to strings[], so that strings[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
    {
        strings[i] = output[i];
        lengths[i]=lens[i];
    }
    free(output);
    free(lens);
}

// The main function to that sorts strings[] of size n using
// Radix Sort
long long int  getMax(long long int  n)
{
    long long int  mx = lengths[0];
    for (long long int  i = 1; i < n; i++)
    {
        if (lengths[i] > mx)
        {
            mx = lengths[i];
        }
    }
    return mx;
}
void myradixsort(long long int  n)
{

    // Find the maximum number to know number of symbols
    long long int  maxlen = getMax(n);
    // Do counting sort for every symbol.
    for (long long int  num = maxlen - 1; num >= 0; num--)
    {
        countSort(n, num);
    }

}
// A utility function to print an array
void print(long long int  n)
{
    for (long long int  i = 0; i < n; i++)
    {
        for (long long int  j = 0; j < lengths[i]; j++)
        {
            printf("%c", strings[i][j]);
        }
        printf("\n");
    }
}
//Driver program to test above functions
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Error! Incorrect number of parameters");
        exit(1);
    }
    long long int  true_n=(long long int )atoi(argv[1]);

    FILE *fptr;
    fptr = fopen(argv[2], "r");
    if (fptr == NULL)
    {
        printf("Error! Incorrect file name %s",argv[2]);
        fclose(fptr);
        exit(2);
    }

    long long int  current_n_for_malloc = startn;
    long long int  current_string_len = startlen;
    strings = malloc(current_n_for_malloc * sizeof(char *));
    if (strings==NULL)
    {
        printf("Memory allocation error!");
        fclose(fptr);
        exit(4);
    }
    char *current_string = malloc(startlen* sizeof(char));
    if (current_string==NULL)
    {
        printf("Memory allocation error!");
        fclose(fptr);
        free(lengths);
        for (long long int  i=0;i<n;i++)
        {
            free(strings[i]);
        }
        free(strings);
        free(current_string);
        exit(4);
    }
    lengths = malloc(current_n_for_malloc * sizeof(long long int ));
    if (lengths==NULL)
    {
        printf("Memory allocation error!");
        fclose(fptr);
        free(lengths);
        for (long long int  i=0;i<n;i++)
        {
            free(strings[i]);
        }
        free(strings);
        free(current_string);
        exit(4);
    }
    long long int  current_string_list_len = 0;
    char c;
    while(n<true_n)
    {
        c = getc(fptr);
        if (c==EOF && ferror(fptr))
        {
            printf("Error! Unexpected EOF");
            fclose(fptr);
            free(lengths);
            for (long long int  i=0;i<n;i++)
            {
                free(strings[i]);
            }
            free(strings);
            free(current_string);
            exit(3);
        }
        if (c==EOF)
        {
            break;
        }
        if (c == '\n')
        {
            strings[n] = current_string;
            lengths[n] = (current_string_list_len);
            n++;
            current_string_list_len = 0;
            current_string = malloc(startlen* sizeof(char));
            current_string_len = startlen;
            if (n + 1 > current_n_for_malloc)
            {
                current_n_for_malloc *= 2;
                strings = realloc(strings, current_n_for_malloc * sizeof(char *));
                if (strings==NULL)
                {
                    printf("Memory allocation error!");
                    fclose(fptr);
                    free(lengths);
                    for (long long int  i=0;i<n;i++)
                    {
                        free(strings[i]);
                    }
                    free(strings);
                    free(current_string);
                    exit(4);
                }
                lengths = realloc(lengths, current_n_for_malloc * sizeof(long long int ));
                if (lengths==NULL)
                {
                    printf("Memory allocation error!");
                    fclose(fptr);
                    free(lengths);
                    for (long long int  i=0;i<n;i++)
                    {
                        free(strings[i]);
                    }
                    free(strings);
                    free(current_string);
                    exit(4);
                }
            }
        }
        else
        {
            current_string[current_string_list_len] = c;
            (current_string_list_len)++;
            if ((current_string_list_len) + 1 > current_string_len)
            {
                current_string_len *= 2;
                current_string = realloc(current_string, (size_t)current_string_len);
                if (current_string==NULL)
                {
                    printf("Memory allocation error!");
                    fclose(fptr);
                    free(lengths);
                    for (long long int  i=0;i<n;i++)
                    {
                        free(strings[i]);
                    }
                    free(strings);
                    free(current_string);
                    exit(4);
                }
            }
        }
    }
    if (current_string_list_len > 0)
    {
        strings[n] = current_string;
        lengths[n] = (current_string_list_len);
        n++;
    }
    char sort_name_first_symbol=argv[3][0];
    switch (sort_name_first_symbol)
    {
        case 'b':
        {
            if (strcmp(argv[3], "bubble") == 0)
            {
                bubbleSort(n);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                fclose(fptr);
                free(lengths);
                for (long long int  i=0;i<n;i++)
                {
                    free(strings[i]);
                }
                free(strings);
                free(current_string);
                exit(1);
            }
            break;
        }
        case 'i':
        {
            if (strcmp(argv[3], "insertion") == 0)
            {
                insertionSort(n);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                fclose(fptr);
                free(lengths);
                for (long long int  i=0;i<n;i++)
                {
                    free(strings[i]);
                }
                free(strings);
                free(current_string);
                exit(1);
            }
            break;
        }
        case 'm':
        {
            if (strcmp(argv[3], "merge") == 0)
            {
                mergeSort(0, n - 1);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                fclose(fptr);
                free(lengths);
                for (long long int  i=0;i<n;i++)
                {
                    free(strings[i]);
                }
                free(strings);
                free(current_string);
                exit(1);
            }
            break;
        }
        case 'q':
        {
            if (strcmp(argv[3], "quick") == 0)
            {
                quickSort(0, n - 1);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                fclose(fptr);
                free(lengths);
                for (long long int  i=0;i<n;i++)
                {
                    free(strings[i]);
                }
                free(strings);
                free(current_string);
                exit(1);
            }
            break;
        }
        case 'r':
        {
            if (strcmp(argv[3], "radix") == 0)
            {
                myradixsort(n);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                fclose(fptr);
                free(lengths);
                for (long long int  i=0;i<n;i++)
                {
                    free(strings[i]);
                }
                free(strings);
                free(current_string);
                exit(1);
            }
            break;
        }
        default:
        {
            printf("Error: Sort %s was not found.", argv[3]);
            fclose(fptr);
            free(lengths);
            for (long long int  i=0;i<n;i++)
            {
                free(strings[i]);
            }
            free(strings);
            free(current_string);
            exit(1);
        }
    }
    print(n);
    fclose(fptr);
    free(lengths);
    for (long long int  i=0;i<n;i++)
    {
        free(strings[i]);
    }
    free(strings);
    //free(current_string);
    return 0;
}
